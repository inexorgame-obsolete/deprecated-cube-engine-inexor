/*
 * EntitySystem.cpp
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#include "EntitySystem.h"
#include <time.h>
#include <cube.h>

#include "domain/TimeStep.h"
#include "provider/TeleportEntityTypeProvider.h"
#include "subsystem/particle/emitter/PointEmitter.h"
#include "subsystem/particle/initializer/PulseInitializer.h"
#include "subsystem/particle/modifier/VelocityTransformation.h"
#include "subsystem/particle/modifier/VectorField.h"

using namespace inexor::entity::particle;

namespace inexor {
namespace entity {

EntitySystem::EntitySystem()
{
    // Reset the time calculation
    ResetTimer();

    // Create type managers
    entity_type_manager = new EntityTypeManager();
    relationship_type_manager = new RelationshipTypeManager(entity_type_manager);

    // Create instance managers
    entity_instance_manager = new EntityInstanceManager(entity_type_manager);
    relationship_instance_manager = new RelationshipInstanceManager(relationship_type_manager);

    // Create subsystems and store it
    teleport_subsystem = new TeleportSubsystem(entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager);
    particle_subsystem = new ParticleSubsystem(entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager);

    // Store the subsystems and it's type(!) in the subsystem type map, so that
    // the concrete subsystem can be retrieved instead of only as SubsystemBase
    //
    // ex: CefRefPtr<TeleportSubsystem> teleport_subsystem = entity_system->GetSubsystem<TeleportSubsystem>();
    //
    subsystemTypeMap.Set<TeleportSubsystem>(teleport_subsystem.get());
    subsystemTypeMap.Set<ParticleSubsystem>(particle_subsystem.get());

    // Store all subsystems in a vector:
    subsystems.push_back(teleport_subsystem);
    subsystems.push_back(particle_subsystem);

}

EntitySystem::~EntitySystem()
{
    Cleanup();
    subsystems.clear();
    subsystemTypeMap.ObjectMap.clear();
}

/**
 * This happens in the main thread.
 */
void EntitySystem::Update()
{
    // Calculate the time step
    frame_millis = SDL_GetTicks();
    elapsed_millis = frame_millis - frame_last_millis;
    TimeStep time_step(
        elapsed_millis,
        (double) elapsed_millis / time_unit,
        time_unit
    );
    for (unsigned int i = 0; i < subsystems.size(); i++)
    {
        SubsystemBase* subsystem = subsystems[i];
        if (!subsystem) throw std::invalid_argument("cannot be null, plz");
        subsystem->Update(time_step);
    }
    frame_last_millis = frame_millis;
}

void EntitySystem::Cleanup()
{
    for (unsigned int i = 0; i < subsystems.size(); i++)
    {
        subsystems[i]->Cleanup();
    }
    // TODO: Cleanup Types and Entities
    // TODO: Stop particle threads
}

void EntitySystem::Reset()
{
    // TODO: cleanup entities, temporarily stop renderers
    for (unsigned int i = 0; i < subsystems.size(); i++)
    {
        subsystems[i]->Reset();
    }
}

void EntitySystem::Save(std::string filename)
{
}

void EntitySystem::Load(std::string filename)
{
}

void EntitySystem::ResetTimer()
{
    frame_millis = frame_last_millis = SDL_GetTicks();
    elapsed_millis = 0;
    time_unit = 1000.0;
}

void EntitySystem::SetTimeUnit(double time_unit)
{
    this->time_unit = time_unit;
}

CefRefPtr<EntityTypeManager> EntitySystem::GetEntityTypeManager()
{
    return entity_type_manager;
}

CefRefPtr<RelationshipTypeManager> EntitySystem::GetRelationshipTypeManager()
{
    return relationship_type_manager;
}

CefRefPtr<EntityInstanceManager> EntitySystem::GetEntityInstanceManager()
{
    return entity_instance_manager;
}

CefRefPtr<RelationshipInstanceManager> EntitySystem::GetRelationshipInstanceManager()
{
    return relationship_instance_manager;
}

// TODO: Test cases
void EntitySystem::RunTests()
{
    SubsystemTest();
    AttributeTest();
    InstanceCreationTest();
    TypeCreationTest();
    ParticleSystemTest();
}

void EntitySystem::SubsystemTest()
{
    logoutf("Try to access subsystems by type");
    CefRefPtr<TeleportSubsystem> teleport_subsystem = this->GetSubsystem<TeleportSubsystem>();
    CefRefPtr<ParticleSubsystem> particle_subsystem = this->GetSubsystem<ParticleSubsystem>();
}

void EntitySystem::InstanceCreationTest()
{
    logoutf("Creating 100000 entity and 100000 relationship instances");
    CefRefPtr<TeleportSubsystem> teleport_subsystem = this->GetSubsystem<TeleportSubsystem>();
    InstanceRefPtr<EntityInstance> teleport1 = teleport_subsystem->CreateTeleport(0.0, 0.0, 0.0);
    InstanceRefPtr<EntityInstance> teledest1 = teleport_subsystem->CreateTeledest(0.0, 0.0, 0.0);
    InstanceRefPtr<RelationshipInstance> teleporting1 = teleport_subsystem->Connect(teleport1, teledest1);
    for (int i = 0; i < 100000; i++)
    {
        InstanceRefPtr<EntityInstance> teledest = teleport_subsystem->CreateTeledest(0.0, 0.0, 0.0);
        InstanceRefPtr<RelationshipInstance> teleporting = teleport_subsystem->Connect(teleport1, teledest);
    }

    logoutf("Entity: Types: %d Instances: %d", entity_type_manager->Size(), entity_instance_manager->Size());
    logoutf("Relationships: Types: %d Instances: %d", relationship_type_manager->Size(), relationship_instance_manager->Size());
}

void EntitySystem::LowLevelTypeCreationTest()
{
    logoutf("Create entity and relationship types (low level)");
    TypeRefPtr<EntityType> source_type = entity_type_manager->Create("source_type", false, false);
    TypeRefPtr<EntityType> target_type = entity_type_manager->Create("target_type", false, false);
    TypeRefPtr<RelationshipType> relationship_type = relationship_type_manager->Create("relationship_type", false, false, source_type, target_type);
    logoutf("Entity: Types: %d Instances: %d", entity_type_manager->Size(), entity_instance_manager->Size());
    logoutf("Relationships: Types: %d Instances: %d", relationship_type_manager->Size(), relationship_instance_manager->Size());
}

void EntitySystem::TypeCreationTest()
{
    logoutf("Create a batch of entity types");
    CefRefPtr<ParticleSubsystem> particle_subsystem = this->GetSubsystem<ParticleSubsystem>();
    for (int i = 0; i < 1000; i++)
    {
        std::string particle_type_name = "default_particle_" + i;
        std::string particle_emitter_type_name = "simple_emitter_" + i;
        std::string test_function_name = "test_function_" + i;
        FunctionRefPtr test_function_i = new EntityFunction(test_function_name);
        TypeRefPtr<EntityType> particle_type_i = particle_subsystem->CreateParticleType(particle_type_name, "default_renderer");
        TypeRefPtr<EntityType> particle_emitter_type_i = particle_subsystem->CreateEmitterType(particle_emitter_type_name, test_function_i, particle_type_i, 100, 1, 1000, 0.1, 1.0);
    }

    logoutf("Entity: Types: %d Instances: %d", entity_type_manager->Size(), entity_instance_manager->Size());
    logoutf("Relationships: Types: %d Instances: %d", relationship_type_manager->Size(), relationship_instance_manager->Size());
    logoutf("[ok] High Level Type Creation Test");
}

void EntitySystem::AttributeTest()
{
    logoutf("Test attributes");
    AttributeRefPtr attr_int_1 = new EntityAttribute(1);
    logoutf("test  1: type: %d expected: %d value: %d", attr_int_1->GetType(), 1, attr_int_1->GetInteger());
    AttributeRefPtr attr_int_2 = 2;
    logoutf("test  2: type: %d expected: %d value: %d", attr_int_2->GetType(), 2, attr_int_2->GetInteger());
    TypeRefPtr<EntityType> et = new EntityType("et1", false, false);
    et->AddAttribute("int1", attr_int_1);
    logoutf("test  3: type: %d expected: %d value: %d", et["int1"]->GetType(), 1, et["int1"]->GetInteger());
    et->AddAttribute("int2", attr_int_2);
    logoutf("test  4: type: %d expected: %d value: %d", et["int2"]->GetType(), 2, et["int2"]->GetInteger());
    AttributeRefPtr attr_double_1 = 3.0;
    et->AddAttribute("double1", attr_double_1);
    logoutf("test  5: type: %d expected: %3f value: %3f", et["double1"]->GetType(), 3.0, et["double1"]->GetDouble());
    logoutf("test  6: type: %d expected: %3f value: %3f", et->GetAttribute("double1")->GetType(), 3.0, et->GetAttribute("double1")->GetDouble());
    et->AddAttribute("double2", 4.0);
    logoutf("test  7: type: %d expected: %3f value: %3f", et["double2"]->GetType(), 4.0, et["double2"]->GetDouble());
    logoutf("test  8: type: %d expected: %3f value: %3f", et->GetAttribute("double2")->GetType(), 4.0, et->GetAttribute("double2")->GetDouble());
    et["int3"] = 5;
    logoutf("test  9: type: %d expected: %d value: %d", et["int3"]->GetType(), 5, et["int3"]->GetInteger());
    et["double3"] = 6.0;
    logoutf("test 10: type: %d expected: %3f value: %3f", et["double3"]->GetType(), 6.0, et["double3"]->GetDouble());
    et["string1"] = std::string("string1");
    logoutf("test 11: type: %d expected: %s value: %s", et["string1"]->GetType(), "string1", et["string1"]->GetString().c_str());
    et["boolfalse"] = false;
    logoutf("test 12: type: %d expected: %d value: %d", et["boolfalse"]->GetType(), 0, et["boolfalse"]->GetBool());
    et["booltrue"] = true;
    logoutf("test 13: type: %d expected: %d value: %d", et["booltrue"]->GetType(), 1, et["booltrue"]->GetBool());
    FunctionRefPtr entAction = new EntityFunction("action1");
    et["function1"] = entAction;
    logoutf("test 14: type: %d expected: %s value: %s", et["function1"]->GetType(), "action1", et["function1"]->GetFunction()->GetName().c_str());
    et["function2"] = (FunctionRefPtr) new EntityFunction("action2");
    logoutf("test 15: type: %d expected: %s value: %s", et["function2"]->GetType(), "action2", et["function2"]->GetFunction()->GetName().c_str());
    TimeStep t(0, 1.0, 1.0);
    et["function2"]->GetFunction()->Execute(t);
    et["function2"]->GetFunction()->Execute(t, et);
    et["function2"]->operator ()(t);
    et["function2"]->operator ()(t, et);
    et["function2"](t);
    et["function2"](t, et);
    InstanceRefPtr<EntityInstance> ei = new EntityInstance(et);
    ei["x"] = 10.0;
    logoutf("test 16: type: %s name: %s type: %d expected: %3f value: %3f", ei->GetType()->GetName().c_str(), ei["x"]->name.c_str(), ei["x"]->type, 10.0, ei["x"]->GetDouble());
    ei["y"] = -10.0;
    logoutf("test 17: type: %s name: %s type: %d expected: %3f value: %3f", ei->GetType()->GetName().c_str(), ei["y"]->name.c_str(), ei["x"]->type, -10.0, ei["y"]->GetDouble());
}

void EntitySystem::ParticleSystemTest()
{
    CefRefPtr<ParticleSubsystem> particle_subsystem = this->GetSubsystem<ParticleSubsystem>();

    logoutf("Create entity function 'PointEmitter'");
    FunctionRefPtr point_emitter_function = new PointEmitter();

    logoutf("Create entity function 'PulseInitializer'");
    FunctionRefPtr pulse_initializer_function = new PulseInitializer();

    logoutf("Create entity function 'VelocityTransformation'");
    FunctionRefPtr velocity_transformation_function = new VelocityTransformation();

    logoutf("Create entity function 'VectorField' with expression 'x * 1.2,y * 1.2,z * 1.2'");
    FunctionRefPtr vector_field_function = new VectorField("x * 1.2,y * 1.2,z * 1.2");

    logoutf("Create a particle type");
    TypeRefPtr<EntityType> default_particle_type = particle_subsystem->CreateParticleType("default_particle", "default_renderer");
    // TypeRefPtr<EntityType> particle_type = entity_type_manager->Create("default_particle", false, false /* , parent */);

    logoutf("Create emitter type 'point_emitter (rate: every 1500ms, lifetime: 1000ms)'");
    TypeRefPtr<EntityType> point_emitter = particle_subsystem->CreateEmitterType("point_emitter", point_emitter_function, default_particle_type, 1250, 1, 1000, 1.0, 1.0);

    logoutf("Create emitter type 'pulse_point_emitter (rate: every 1250ms, lifetime: 250ms)'");
    TypeRefPtr<EntityType> pulse_point_emitter = particle_subsystem->CreateEmitterType("pulse_point_emitter", point_emitter_function, default_particle_type, 1250, 250);

    logoutf("Create modifier type 'velocity_transformation_modifier'");
    TypeRefPtr<EntityType> velocity_transformation_modifier_type = particle_subsystem->CreateModifierType("velocity_transformation_modifier", velocity_transformation_function);

    // modifier_type["modify"]
    // TODO: CreateModifierType("vector_field_modifier", vector_field_function)
    // TODO: SetModifierFunction(vector_field_function)
    logoutf("Create modifier type 'vector_field_modifier'");
    TypeRefPtr<EntityType> vector_field_modifier_type = particle_subsystem->CreateModifierType("vector_field_modifier", vector_field_function);

    /*
    logoutf("Create a particle instance");
    InstanceRefPtr<EntityInstance> particle = new EntityInstance(default_particle_type);
    particle["x"] = 0.0;
    particle["y"] = 0.0;
    particle["z"] = 0.0;
    particle["vx"] = 1.0;
    particle["vy"] = 2.0;
    particle["vz"] = 3.0;
    logoutf("    x: %2.2f y: %2.2f z: %2.2f vx: %2.2f vy: %2.2f vz: %2.2f", particle["x"]->GetDouble(), particle["y"]->GetDouble(), particle["z"]->GetDouble(), particle["vx"]->GetDouble(), particle["vy"]->GetDouble(), particle["vz"]->GetDouble());

    logoutf("Apply modifier 'velocity_transformation_modifier' with different approaches");
    // a full time unit elapsed
    TimeStep tf(0, 1.0, 1.0);
    velocity_transformation_function->Execute(tf, particle.get());
    logoutf("     x: %2.2f y: %2.2f z: %2.2f vx: %2.2f vy: %2.2f vz: %2.2f", particle["x"]->GetDouble(), particle["y"]->GetDouble(), particle["z"]->GetDouble(), particle["vx"]->GetDouble(), particle["vy"]->GetDouble(), particle["vz"]->GetDouble());
    velocity_transformation_function(tf, particle.get());
    logoutf("     x: %2.2f y: %2.2f z: %2.2f vx: %2.2f vy: %2.2f vz: %2.2f", particle["x"]->GetDouble(), particle["y"]->GetDouble(), particle["z"]->GetDouble(), particle["vx"]->GetDouble(), particle["vy"]->GetDouble(), particle["vz"]->GetDouble());
    FunctionRefPtr vt_mt = velocity_transformation_modifier_type["modify"]->GetFunction();
    vt_mt(tf, particle.get());
    logoutf("     x: %2.2f y: %2.2f z: %2.2f vx: %2.2f vy: %2.2f vz: %2.2f", particle["x"]->GetDouble(), particle["y"]->GetDouble(), particle["z"]->GetDouble(), particle["vx"]->GetDouble(), particle["vy"]->GetDouble(), particle["vz"]->GetDouble());

    logoutf("Apply modifier 'vector_field_modifier' and 'velocity_transformation_modifier' multiple times");
    TimeStep vf_tf(0, 0.1, 1.0);
    FunctionRefPtr vf_mt = vector_field_modifier_type["modify"]->GetFunction();
    for (int i = 0; i < 10; i++) {
        SDL_Delay(10);
        vf_mt(vf_tf, particle.get());
        logoutf("    vx: %2.2f vy: %2.2f vz: %2.2f", particle["vx"]->GetDouble(), particle["vy"]->GetDouble(), particle["vz"]->GetDouble());
        vt_mt(vf_tf, particle.get());
        logoutf("     x: %2.2f  y: %2.2f  z: %2.2f", particle["x"]->GetDouble(), particle["y"]->GetDouble(), particle["z"]->GetDouble());
    }
    */

    // Create emitter instances
    logoutf("Create emitter instances");
    InstanceRefPtr<EntityInstance> point_emitter_1 = particle_subsystem->CreateEmitterInstance(point_emitter, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
/*
    InstanceRefPtr<EntityInstance> point_emitter_2 = particle_subsystem->CreateEmitterInstance(point_emitter, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0);
    InstanceRefPtr<EntityInstance> point_emitter_3 = particle_subsystem->CreateEmitterInstance(point_emitter, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    InstanceRefPtr<EntityInstance> point_emitter_4 = particle_subsystem->CreateEmitterInstance(point_emitter, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0);
    InstanceRefPtr<EntityInstance> pulse_point_emitter_1 = particle_subsystem->CreateEmitterInstance(pulse_point_emitter, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    InstanceRefPtr<EntityInstance> pulse_point_emitter_2 = particle_subsystem->CreateEmitterInstance(pulse_point_emitter, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
*/

    // Create modifier instances
    logoutf("Create modifier instances");
    InstanceRefPtr<EntityInstance> velocity_transformation_modifier_1 = particle_subsystem->CreateModifierInstance(velocity_transformation_modifier_type);

    // This creates an relation from an emitter to an modifier
    logoutf("Create relation from emitter to modifier");
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_velocity_1 = particle_subsystem->AddModifierToEmitter(point_emitter_1, velocity_transformation_modifier_1);
/*
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_velocity_2 = particle_subsystem->AddModifierToEmitter(point_emitter_2, velocity_transformation_modifier_1);
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_velocity_3 = particle_subsystem->AddModifierToEmitter(point_emitter_3, velocity_transformation_modifier_1);
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_velocity_4 = particle_subsystem->AddModifierToEmitter(point_emitter_4, velocity_transformation_modifier_1);
    InstanceRefPtr<RelationshipInstance> rel_pulse_point_velocity_1 = particle_subsystem->AddModifierToEmitter(pulse_point_emitter_1, velocity_transformation_modifier_1);
    InstanceRefPtr<RelationshipInstance> rel_pulse_point_velocity_2 = particle_subsystem->AddModifierToEmitter(pulse_point_emitter_2, velocity_transformation_modifier_1);
*/

/*
    logoutf("Fire emitter 1: Call function directly");
    point_emitter_function->Execute(vf_tf, default_particle_type, point_emitter_1);

    logoutf("Fire emitter 2: Retrieve function first, then call it");
    FunctionRefPtr point_emitter_function_2 = point_emitter_1->GetType()->GetAttribute("emit")->GetFunction();
    point_emitter_function_2(vf_tf, default_particle_type, point_emitter_1);

    logoutf("Fire emitter 3: Long(est) version: Get Type, then the attribute, then the function, then execute it");
    point_emitter_1->GetType()->GetAttribute("emit")->GetFunction()->Execute(vf_tf, default_particle_type, point_emitter_1);

    logoutf("Fire emitter 4: Shorter version: Call the attribute of the type");
    point_emitter_1->GetType()["emit"](vf_tf, default_particle_type, point_emitter_1);
*/

    logoutf("Finished particle system tests");
}

}
}
