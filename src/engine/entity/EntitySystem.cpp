/*
 * EntitySystem.cpp
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#include "EntitySystem.h"
#include <time.h>
#include <cube.h>
#include <entity/subsystem/particle/initializer/RandomVelocity.h>

#include "domain/TimeStep.h"
#include "provider/TeleportEntityTypeProvider.h"
#include "subsystem/particle/emitter/Point.h"
#include "subsystem/particle/initializer/RandomPosition.h"
#include "subsystem/particle/initializer/RandomVelocity.h"
#include "subsystem/particle/modifier/DensityFadeout.h"
#include "subsystem/particle/modifier/GeometryCollide.h"
#include "subsystem/particle/modifier/GravityPoint.h"
#include "subsystem/particle/modifier/SimpleGravity.h"
#include "subsystem/particle/modifier/Rolling.h"
#include "subsystem/particle/modifier/VelocityTransformation.h"
#include "subsystem/particle/modifier/VectorField.h"
#include "subsystem/particle/renderer/Billboard.h"
#include "subsystem/particle/renderer/Cube.h"
#include "subsystem/particle/renderer/Model.h"
#include "subsystem/particle/renderer/Origin.h"

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

    // Start worker threads (doesn't work!!!)
    // relationship_instance_manager->Start();
}

EntitySystem::~EntitySystem()
{
    // Stop worker threads
    relationship_instance_manager->Stop();

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
    TimeStep time_step(elapsed_millis, time_unit);
    for (unsigned int i = 0; i < subsystems.size(); i++)
    {
        subsystems[i]->Update(time_step);
    }
    // Cleanup invalidated relationships
    relationship_instance_manager->Invalidate();
    relationship_instance_manager->DoCreateInstances();
    frame_last_millis = frame_millis;
}

void EntitySystem::Cleanup()
{
    for (unsigned int i = 0; i < subsystems.size(); i++)
    {
        subsystems[i]->Cleanup();
    }
    // TODO: Cleanup Types and Entities
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
    // SubsystemTest();
    // AttributeTest();
    // InstanceCreationTest();
    // TypeCreationTest();
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

    logoutf("Create entity function 'Point'");
    FunctionRefPtr point_emitter_function = new Point();

    logoutf("Create entity function 'RandomPosition'");
    FunctionRefPtr random_position_function = new RandomPosition();

    logoutf("Create entity function 'RandomVelocity'");
    FunctionRefPtr random_velocity_function = new RandomVelocity();

    logoutf("Create entity function 'DensityFadeout'");
    FunctionRefPtr density_fadeout_function = new DensityFadeout();

    logoutf("Create entity function 'GeometryCollide'");
    FunctionRefPtr geometry_collide_function = new GeometryCollide();

    logoutf("Create entity function 'GravityPoint'");
    FunctionRefPtr gravity_point_function = new GravityPoint();

    logoutf("Create entity function 'VelocityTransformation'");
    FunctionRefPtr velocity_transformation_function = new VelocityTransformation();

    logoutf("Create entity function 'VectorField' with expression '(z * -0.3) * x, (z * -0.2) * y, z + 20'");
    FunctionRefPtr vector_field_function = new VectorField("(z * -0.3) * x, (z * -0.2) * y, 20");

    logoutf("Create entity function 'SimpleGravity'");
    FunctionRefPtr simple_gravity_function = new SimpleGravity();

    logoutf("Create entity function 'Rolling'");
    FunctionRefPtr rolling_function = new Rolling();

    logoutf("Create entity function 'Billboard'");
    FunctionRefPtr billboard_renderer_function = new Billboard();

    logoutf("Create entity function 'Cube'");
    FunctionRefPtr cube_renderer_function = new Cube();

    logoutf("Create entity function 'Model'");
    FunctionRefPtr model_renderer_function = new Model();

    logoutf("Create entity function 'Origin'");
    FunctionRefPtr origin_renderer_function = new Origin();


    logoutf("Create a particle type");
    TypeRefPtr<EntityType> default_particle_type = particle_subsystem->CreateParticleType("default_particle", "default_renderer");

    logoutf("Create emitter type 'point_emitter (rate: every 250ms, lifetime: 2500ms)'");
    TypeRefPtr<EntityType> point_emitter = particle_subsystem->CreateEmitterType("point_emitter", point_emitter_function, default_particle_type, 75, 10, 5000, 1.0, 1.0);

    logoutf("Create initializer type 'random_position_initializer'");
    TypeRefPtr<EntityType> random_position_initializer_type = particle_subsystem->CreateInitializerType("random_position_initializer", random_position_function);

    logoutf("Create initializer type 'random_velocity_initializer'");
    TypeRefPtr<EntityType> random_velocity_initializer_type = particle_subsystem->CreateInitializerType("random_velocity_initializer", random_velocity_function);

    logoutf("Create modifier type 'density_fadeout_modifier'");
    TypeRefPtr<EntityType> density_fadeout_modifier_type = particle_subsystem->CreateModifierType("density_fadeout_modifier", density_fadeout_function);

    logoutf("Create modifier type 'geometry_collide_modifier'");
    TypeRefPtr<EntityType> geometry_collide_modifier_type = particle_subsystem->CreateModifierType("geometry_collide_modifier", geometry_collide_function);

    logoutf("Create modifier type 'gravity_point_modifier'");
    TypeRefPtr<EntityType> gravity_point_modifier_type = particle_subsystem->CreateModifierType("gravity_point_modifier", gravity_point_function);

    logoutf("Create modifier type 'velocity_transformation_modifier'");
    TypeRefPtr<EntityType> velocity_transformation_modifier_type = particle_subsystem->CreateModifierType("velocity_transformation_modifier", velocity_transformation_function);

    logoutf("Create modifier type 'vector_field_modifier'");
    TypeRefPtr<EntityType> vector_field_modifier_type = particle_subsystem->CreateModifierType("vector_field_modifier", vector_field_function);
    vector_field_modifier_type[EXPRESSION] = std::string("(z * -0.3) * x, (z * -0.2) * y, 20");

    logoutf("Create modifier type 'simple_gravity_modifier'");
    TypeRefPtr<EntityType> simple_gravity_modifier_type = particle_subsystem->CreateModifierType("simple_gravity_modifier", simple_gravity_function);

    logoutf("Create modifier type 'rolling_modifier'");
    TypeRefPtr<EntityType> rolling_modifier_type = particle_subsystem->CreateModifierType("rolling_modifier", rolling_function);

    logoutf("Create renderer type 'billboard_renderer'");
    TypeRefPtr<EntityType> billboard_renderer_type = particle_subsystem->CreateRendererType("billboard_renderer", billboard_renderer_function);

    logoutf("Create renderer type 'cube_renderer'");
    TypeRefPtr<EntityType> cube_renderer_type = particle_subsystem->CreateRendererType("cube_renderer", cube_renderer_function);

    logoutf("Create renderer type 'model_renderer'");
    TypeRefPtr<EntityType> model_renderer_type = particle_subsystem->CreateRendererType("model_renderer", model_renderer_function);

    logoutf("Create renderer type 'origin_renderer'");
    TypeRefPtr<EntityType> origin_renderer_type = particle_subsystem->CreateRendererType("origin_renderer", origin_renderer_function);


    logoutf("Create emitter instances");
    InstanceRefPtr<EntityInstance> point_emitter_1 = particle_subsystem->CreateEmitterInstance(point_emitter, 512.0, 768.0, 512.0, 0.0, 0.0, 0.0);
    InstanceRefPtr<EntityInstance> point_emitter_2 = particle_subsystem->CreateEmitterInstance(point_emitter, 512.0, 256.0, 512.0, 0.0, 0.0, 0.0);
    point_emitter_2[LIFETIME] = 7500;
    InstanceRefPtr<EntityInstance> point_emitter_3 = particle_subsystem->CreateEmitterInstance(point_emitter, 768.0, 512.0, 542.0, 0.0, 0.0, 0.0);
    point_emitter_3[RATE] = 250;
    point_emitter_3[LIFETIME] = 15000;
    point_emitter_3[BATCH_SIZE] = 1;
    InstanceRefPtr<EntityInstance> point_emitter_4 = particle_subsystem->CreateEmitterInstance(point_emitter, 256.0, 512.0, 512.0, 0.0, 0.0, 0.0);

    logoutf("Create initializer instances");
    InstanceRefPtr<EntityInstance> random_velocity_initializer_1 = particle_subsystem->CreateInitializerInstance(random_velocity_initializer_type);
    random_velocity_initializer_1[DELTA] = vec(15.0f, 15.0f, 10.0f);
    InstanceRefPtr<EntityInstance> random_velocity_initializer_2 = particle_subsystem->CreateInitializerInstance(random_velocity_initializer_type);
    random_velocity_initializer_2[DELTA] = vec(15.0f, 15.0f, 40.0f);
    InstanceRefPtr<EntityInstance> random_position_initializer_1 = particle_subsystem->CreateInitializerInstance(random_position_initializer_type);
    random_position_initializer_1[DELTA] = vec(25.0f, 25.0f, 0.0f);
    InstanceRefPtr<EntityInstance> random_position_initializer_2 = particle_subsystem->CreateInitializerInstance(random_position_initializer_type);
    random_position_initializer_2[DELTA] = vec(5.0f, 5.0f, 5.0f);

    logoutf("Create modifier instances");
    InstanceRefPtr<EntityInstance> velocity_transformation_modifier_1 = particle_subsystem->CreateModifierInstance(velocity_transformation_modifier_type);
    InstanceRefPtr<EntityInstance> vector_field_modifier_1 = particle_subsystem->CreateModifierInstance(vector_field_modifier_type);
    vector_field_modifier_1[POS] = vec(512.0f, 768.0f, 480.0f);
    InstanceRefPtr<EntityInstance> simple_gravity_modifier_1 = particle_subsystem->CreateModifierInstance(simple_gravity_modifier_type);
    InstanceRefPtr<EntityInstance> rolling_modifier_1 = particle_subsystem->CreateModifierInstance(rolling_modifier_type);
    InstanceRefPtr<EntityInstance> geometry_collide_modifier_1 = particle_subsystem->CreateModifierInstance(geometry_collide_modifier_type);
    InstanceRefPtr<EntityInstance> gravity_point_modifier_1 = particle_subsystem->CreateModifierInstance(gravity_point_modifier_type);
    gravity_point_modifier_1[MASS] = 5000.0f;
    gravity_point_modifier_1[GRAVITY] = 15.0f;
    gravity_point_modifier_1[POS] = vec(512.0f - 64.0f, 256.0f, 512.0f + 64.0f);
    InstanceRefPtr<EntityInstance> gravity_point_modifier_2 = particle_subsystem->CreateModifierInstance(gravity_point_modifier_type);
    gravity_point_modifier_2[MASS] = 5000.0f;
    gravity_point_modifier_2[GRAVITY] = 15.0f;
    gravity_point_modifier_2[POS] = vec(512.0f + 64.0f, 256.0f, 512.0f + 64.0f);
    /*
    InstanceRefPtr<EntityInstance> gravity_point_modifier_3 = particle_subsystem->CreateModifierInstance(gravity_point_modifier_type);
    gravity_point_modifier_3[MASS] = 5000.0f;
    gravity_point_modifier_3[GRAVITY] = 15.0f;
    gravity_point_modifier_3[POS] = vec(512.0f, 256.0f + 96.0f, 562.0f);
    InstanceRefPtr<EntityInstance> gravity_point_modifier_4 = particle_subsystem->CreateModifierInstance(gravity_point_modifier_type);
    gravity_point_modifier_4[MASS] = 5000.0f;
    gravity_point_modifier_4[GRAVITY] = 15.0f;
    gravity_point_modifier_4[POS] = vec(512.0f, 256.0f - 96.0f, 562.0f);
    */

    logoutf("Create renderer instances");
    InstanceRefPtr<EntityInstance> billboard_renderer_1 = particle_subsystem->CreateRendererInstance(billboard_renderer_type, "particlepoints", "media/particle/ball1.png", 10.0f);
    InstanceRefPtr<EntityInstance> billboard_renderer_2 = particle_subsystem->CreateRendererInstance(billboard_renderer_type, "particlepoints", "media/particle/ball2.png", 5.0f);
    InstanceRefPtr<EntityInstance> billboard_renderer_3 = particle_subsystem->CreateRendererInstance(billboard_renderer_type, "particlepoints", "media/particle/ball3.png", 8.0f);
    InstanceRefPtr<EntityInstance> model_renderer_1 = particle_subsystem->CreateRendererInstance(model_renderer_type, "projectile/grenade", vec(0.0f, 0.0f, 2.0f));
    InstanceRefPtr<EntityInstance> cube_renderer_1 = particle_subsystem->CreateRendererInstance(cube_renderer_type, "particlepoints", "media/particle/ball3.png", 3.0f);
    InstanceRefPtr<EntityInstance> origin_renderer_1 = particle_subsystem->CreateRendererInstance(origin_renderer_type, "particlepoints", "media/particle/ball3.png", 3.0f);


    logoutf("Create relation from emitter to initializer");
    // InstanceRefPtr<RelationshipInstance> rel_point_emitter_random_velocity_1 = particle_subsystem->AddInitializerToEmitter(point_emitter_1, random_velocity_initializer_1);
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_random_position_1 = particle_subsystem->AddInitializerToEmitter(point_emitter_1, random_position_initializer_1);
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_random_velocity_2 = particle_subsystem->AddInitializerToEmitter(point_emitter_2, random_velocity_initializer_1);
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_random_velocity_3 = particle_subsystem->AddInitializerToEmitter(point_emitter_3, random_velocity_initializer_2);
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_random_velocity_4 = particle_subsystem->AddInitializerToEmitter(point_emitter_4, random_velocity_initializer_1);
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_random_position_4 = particle_subsystem->AddInitializerToEmitter(point_emitter_4, random_position_initializer_2);

    logoutf("Create relation from emitter to modifier");
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_velocity_transformation_1 = particle_subsystem->AddModifierToEmitter(point_emitter_1, velocity_transformation_modifier_1);
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_vector_field_1 = particle_subsystem->AddModifierToEmitter(point_emitter_1, vector_field_modifier_1);
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_velocity_transformation_2 = particle_subsystem->AddModifierToEmitter(point_emitter_2, velocity_transformation_modifier_1);
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_gravity_point_modifier_2_1 = particle_subsystem->AddModifierToEmitter(point_emitter_2, gravity_point_modifier_1);
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_gravity_point_modifier_2_2 = particle_subsystem->AddModifierToEmitter(point_emitter_2, gravity_point_modifier_2);
    // InstanceRefPtr<RelationshipInstance> rel_point_emitter_gravity_point_modifier_2_3 = particle_subsystem->AddModifierToEmitter(point_emitter_2, gravity_point_modifier_3);
    // InstanceRefPtr<RelationshipInstance> rel_point_emitter_gravity_point_modifier_2_4 = particle_subsystem->AddModifierToEmitter(point_emitter_2, gravity_point_modifier_4);
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_velocity_transformation_3 = particle_subsystem->AddModifierToEmitter(point_emitter_3, velocity_transformation_modifier_1);
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_rolling_1 = particle_subsystem->AddModifierToEmitter(point_emitter_3, rolling_modifier_1);
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_simple_gravity_1 = particle_subsystem->AddModifierToEmitter(point_emitter_3, simple_gravity_modifier_1);
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_geometry_collide_modifier_1 = particle_subsystem->AddModifierToEmitter(point_emitter_3, geometry_collide_modifier_1);
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_velocity_transformation_4 = particle_subsystem->AddModifierToEmitter(point_emitter_4, velocity_transformation_modifier_1);

    logoutf("Create relation from emitter to renderer");
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_billboard_renderer_1 = particle_subsystem->AddRendererToEmitter(point_emitter_1, billboard_renderer_1);
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_billboard_renderer_2 = particle_subsystem->AddRendererToEmitter(point_emitter_2, billboard_renderer_2);
    // InstanceRefPtr<RelationshipInstance> rel_point_emitter_origin_renderer_1 = particle_subsystem->AddRendererToEmitter(point_emitter_2, origin_renderer_1);
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_model_renderer_1 = particle_subsystem->AddRendererToEmitter(point_emitter_3, model_renderer_1);
    // InstanceRefPtr<RelationshipInstance> rel_point_emitter_cube_renderer_1 = particle_subsystem->AddRendererToEmitter(point_emitter_4, cube_renderer_1);
    InstanceRefPtr<RelationshipInstance> rel_point_emitter_billboard_renderer_3 = particle_subsystem->AddRendererToEmitter(point_emitter_4, billboard_renderer_3);

}

}
}
