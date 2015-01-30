/*
 * EntitySystem.cpp
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#include "EntitySystem.h"
#include <time.h>
#include <cube.h>

#include "provider/TeleportEntityTypeProvider.h"
#include "subsystem/particle/emitter/PointEmitter.h"
#include "subsystem/particle/initializer/PulseInitializer.h"
#include "subsystem/particle/modifier/VelocityTransformation.h"
#include "subsystem/particle/modifier/VectorField.h"

EntitySystem::EntitySystem()
{
    // Create type managers
    entity_type_manager = new EntityTypeManager();
    relationship_type_manager = new RelationshipTypeManager();

    // Create instance managers
    entity_instance_manager = new EntityInstanceManager(entity_type_manager);
    relationship_instance_manager = new RelationshipInstanceManager(relationship_type_manager);

    // Create subsystems
    CefRefPtr<TeleportSubsystem> teleport_subsystem = new TeleportSubsystem(entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager);
    CefRefPtr<ParticleSubsystem> particle_subsystem = new ParticleSubsystem(entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager);
    subsystems.Set<TeleportSubsystem>(teleport_subsystem);
    subsystems.Set<ParticleSubsystem>(particle_subsystem);

    SubsystemTest();
    AttributeTest();
    InstanceCreationTest();
    TypeCreationTest();
    ParticleSystemTest();

}

void EntitySystem::SubsystemTest()
{
    CefRefPtr<TeleportSubsystem> teleport_subsystem = this->GetSubsystem<TeleportSubsystem>();
    CefRefPtr<ParticleSubsystem> particle_subsystem = this->GetSubsystem<ParticleSubsystem>();
    logoutf("[ok] Subsystem Tests");
}

void EntitySystem::InstanceCreationTest()
{
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
    logoutf("[ok] Instance Creation Test");
}

void EntitySystem::LowLevelTypeCreationTest()
{
    TypeRefPtr<EntityType> source_type = entity_type_manager->Create("source_type", false, false);
    TypeRefPtr<EntityType> target_type = entity_type_manager->Create("target_type", false, false);
    TypeRefPtr<RelationshipType> relationship_type = relationship_type_manager->Create("relationship_type", false, false, source_type, target_type);
    logoutf("Entity: Types: %d Instances: %d", entity_type_manager->Size(), entity_instance_manager->Size());
    logoutf("Relationships: Types: %d Instances: %d", relationship_type_manager->Size(), relationship_instance_manager->Size());
    logoutf("[ok] Low Level Type Creation Test");
}

void EntitySystem::TypeCreationTest()
{
    logoutf("     Type Creation Tests");
    CefRefPtr<ParticleSubsystem> particle_subsystem = this->GetSubsystem<ParticleSubsystem>();

    for (int i = 0; i < 5; i++)
    {
        std::string particle_type_name = "default_particle_" + i;
        std::string particle_emitter_type_name = "simple_emitter_" + i;
        TypeRefPtr<EntityType> default_particle_type = particle_subsystem->CreateParticleType(particle_type_name);
        TypeRefPtr<EntityType> simple_particle_emitter_type = particle_subsystem->CreateEmitterType(particle_emitter_type_name);
    }

    logoutf("Entity: Types: %d Instances: %d", entity_type_manager->Size(), entity_instance_manager->Size());
    logoutf("Relationships: Types: %d Instances: %d", relationship_type_manager->Size(), relationship_instance_manager->Size());
    logoutf("[ok] High Level Type Creation Test");
}

void EntitySystem::AttributeTest()
{
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
    logoutf("[ok] Attribute Tests");

    /*
    particle_renderer_type* pr_type_ball = ps.add_particle_renderer_type("ball_renderer", "media/particle/flash01.png", "shader", vec4(255.0f, 255.0f, 255.0f, 0.0f), "billboard_renderer");
particle_renderer_instance* pr_inst_ball = pr_type_ball->create_instance("ball_renderer_10");
pr_inst_ball->attributes["size"] = 40.0f;
particle_type* p_type_ball = ps.add_particle_type("ball_10", pr_inst_ball);

particle_modifier_type* pm_type_velocity_transformation = ps.add_particle_modifier_type("velocity_transformation", "velocity_transformation");
particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();
particle_modifier_type* pm_type_simple_gravity = ps.add_particle_modifier_type("global_gravity_10", "simple_gravity");
particle_modifier_instance* pm_inst_simple_gravity = pm_type_simple_gravity->create_instance();
particle_modifier_type* pm_type_geometry_collide = ps.add_particle_modifier_type("geometry_collide_10", "geometry_collide");
particle_modifier_instance* pm_inst_geometry_collide = pm_type_geometry_collide->create_instance();
pm_inst_geometry_collide->attributes["elasticity"] = 0.75f;
particle_initializer_type* pi_type_random_velocity = ps.add_particle_initializer_type("random_velocity_10", "random_velocity");
pi_type_random_velocity->attributes["osx"] = 100.0f;
pi_type_random_velocity->attributes["osy"] = 100.0f;
pi_type_random_velocity->attributes["osz"] = 100.0f;
pi_type_random_velocity->attributes["isx"] = 50.0f;
pi_type_random_velocity->attributes["isy"] = 50.0f;
pi_type_random_velocity->attributes["isz"] = 0.0f;
particle_initializer_instance* pi_inst_random_velocity = pi_type_random_velocity->create_instance();
particle_emitter_type* pe_type_point_ball = ps.add_particle_emitter_type("point_ball_emitter_10", p_type_ball, mass, density, lifetime, rate, "point_emitter");
particle_emitter_instance* pe_inst_point_ball = pe_type_point_ball->create_instance(vec(512.0f, 512.0f, 550.0f), vec(10.0f, 0.0f, 0.0f));
pe_inst_point_ball->add_modifier(pm_inst_velocity_transformation);
pe_inst_point_ball->add_modifier(pm_inst_simple_gravity);

*/

}

void EntitySystem::ParticleSystemTest()
{
    CefRefPtr<ParticleSubsystem> particle_subsystem = this->GetSubsystem<ParticleSubsystem>();

    FunctionRefPtr point_emit = new PointEmitter();
    FunctionRefPtr pulse_init = new PulseInitializer();
    FunctionRefPtr velocity_transformation_function = new VelocityTransformation();
    FunctionRefPtr vector_field_function = new VectorField("x * 1.2,y * 1.2,z * 1.2");

    TypeRefPtr<EntityType> point_emitter = particle_subsystem->CreateEmitterType("point_emitter");
    point_emitter["rate"] = 4;
    point_emitter["lifetime"] = 0.0;
    point_emitter["mass"] = 0.1;
    point_emitter["density"] = 1.0;
    point_emitter["vel_x"] = 1.0;
    point_emitter["vel_y"] = 1.0;
    point_emitter["vel_z"] = 1.0;
    point_emitter["emit"] = point_emit; // Usage 1

    TypeRefPtr<EntityType> pulse_point_emitter = particle_subsystem->CreateEmitterType("pulse_point_emitter");
    pulse_point_emitter["emit"] = point_emit; // Usage 2
    pulse_point_emitter["initialize"] = pulse_init; // But this time let an initializer make particles scattering

    TypeRefPtr<EntityType> velocity_transformation_modifier_type = particle_subsystem->CreateModifierType("velocity_transformation_modifier");
    velocity_transformation_modifier_type["modify"] = velocity_transformation_function;
    velocity_transformation_modifier_type["x"] = 0.1;
    velocity_transformation_modifier_type["y"] = 2.2;
    velocity_transformation_modifier_type["z"] = 0.9;

    // modifier_type["modify"]
    // TODO: CreateModifierType("vector_field_modifier", vector_field_function)
    // TODO: SetModifierFunction(vector_field_function)
    TypeRefPtr<EntityType> vector_field_modifier_type = particle_subsystem->CreateModifierType("vector_field_modifier");
    vector_field_modifier_type["modify"] = vector_field_function;
    vector_field_modifier_type["x"] = 0.1;
    vector_field_modifier_type["y"] = 2.2;
    vector_field_modifier_type["z"] = 0.9;

    TypeRefPtr<EntityType> particle_type = entity_type_manager->Create("particle", false, false /* , parent */);
    InstanceRefPtr<EntityInstance> particle = new EntityInstance(particle_type);
    particle["x"] = 0.0;
    particle["y"] = 0.0;
    particle["z"] = 0.0;
    particle["vx"] = 1.0;
    particle["vy"] = 2.0;
    particle["vz"] = 3.0;
    logoutf("x: %2.2f y: %2.2f z: %2.2f vx: %2.2f vy: %2.2f vz: %2.2f", particle["x"]->GetDouble(), particle["y"]->GetDouble(), particle["z"]->GetDouble(), particle["vx"]->GetDouble(), particle["vy"]->GetDouble(), particle["vz"]->GetDouble());

    // a full time unit elapsed
    TimeStep tf(0, 1.0, 1.0);
    velocity_transformation_function->Execute(tf, particle.get());
    logoutf("x: %2.2f y: %2.2f z: %2.2f vx: %2.2f vy: %2.2f vz: %2.2f", particle["x"]->GetDouble(), particle["y"]->GetDouble(), particle["z"]->GetDouble(), particle["vx"]->GetDouble(), particle["vy"]->GetDouble(), particle["vz"]->GetDouble());
    velocity_transformation_function(tf, particle.get());
    logoutf("x: %2.2f y: %2.2f z: %2.2f vx: %2.2f vy: %2.2f vz: %2.2f", particle["x"]->GetDouble(), particle["y"]->GetDouble(), particle["z"]->GetDouble(), particle["vx"]->GetDouble(), particle["vy"]->GetDouble(), particle["vz"]->GetDouble());

    FunctionRefPtr vt_mt = velocity_transformation_modifier_type["modify"]->GetFunction();
    vt_mt(tf, particle.get());
    logoutf("x: %2.2f y: %2.2f z: %2.2f vx: %2.2f vy: %2.2f vz: %2.2f", particle["x"]->GetDouble(), particle["y"]->GetDouble(), particle["z"]->GetDouble(), particle["vx"]->GetDouble(), particle["vy"]->GetDouble(), particle["vz"]->GetDouble());

    logoutf("vector field");
    TimeStep vf_tf(0, 0.1, 1.0);
    FunctionRefPtr vf_mt = vector_field_modifier_type["modify"]->GetFunction();
    for (int i = 0; i < 10; i++) {
        SDL_Delay(10);
        vf_mt(vf_tf, particle.get());
        logoutf("vx: %2.2f vy: %2.2f vz: %2.2f", particle["vx"]->GetDouble(), particle["vy"]->GetDouble(), particle["vz"]->GetDouble());
        vt_mt(vf_tf, particle.get());
        logoutf("x: %2.2f y: %2.2f z: %2.2f", particle["x"]->GetDouble(), particle["y"]->GetDouble(), particle["z"]->GetDouble());
    }

    // Create emitter and modifier instances
    InstanceRefPtr<EntityInstance> point_emitter_1 = particle_subsystem->CreateEmitterInstance(point_emitter, 0.0, 0.0, 0.0);
    InstanceRefPtr<EntityInstance> pulse_point_emitter_1 = particle_subsystem->CreateEmitterInstance(pulse_point_emitter, 0.0, 0.0, 0.0);
    InstanceRefPtr<EntityInstance> velocity_transformation_modifier_1 = particle_subsystem->CreateModifierInstance(velocity_transformation_modifier_type);

    // This creates an relation from an emitter to an modifier
    InstanceRefPtr<RelationshipInstance> point_emitter_velocity = particle_subsystem->AddModifierToEmitter(point_emitter_1, velocity_transformation_modifier_1);
    InstanceRefPtr<RelationshipInstance> pulse_point_velocity = particle_subsystem->AddModifierToEmitter(pulse_point_emitter_1, velocity_transformation_modifier_1);

    // particle_subsystem->LetThemDie();
    // particle_subsystem->ProcessEmitters();
    // particle_subsystem->ProcessInitializers();
    // particle_subsystem->ProcessModifiers();

    // pulse_point_emitter["emit"]();
    // pulse_point_emitter["initialize"]();
    // velocity_transformation_modifier["modify"]();

    // TypeRefPtr<EntityInstance> point_emitter_1 = particle_subsystem->CreateParticleEmitterInstance(point_emitter, x, y, z);
    // param1: entweder über typerefptr oder über namen
    // positionen: entweder keine, x,y,z oder vec3/vec4
    // point_emitter["x"] = 10.0;
    // point_emitter["y"] = 10.0;
    // point_emitter["z"] = -10.0;

    // Emitter-Instanzen werden der Emitter-Verarbeitungswarteschlange hinzugefügt
    // Main-Loop für Emitter
    // Main-Loop für Modifier
    // Main-Loop für Renderer
    //
    // Modifier haben Referenzen auf ihre Partikel
    // Renderer haben Referenzen auf ihre Partikel
    //
    // processing_queue->push_back(point_emitter_instance);
    // processing_queue->push_back(velocity_transformation_modifier_instance);

    // InstanceFactory
    // Emitter is/uses an InstanceFactory

    // Fiese Thread-Safety: wir haben mehrere processing queues und jeweils einen thread pro queue

    // Ein Emitter/Modifier/usw wird beim hinzufügen zur processing queue gecheckt, ob z.b. ein attribut fehlt.
    // In der processing queue werden bestimmte dinge gecached z.b. positionen

    logoutf("[ok] Particle System Tests");
}

void EntitySystem::Save(std::string filename)
{
}

void EntitySystem::Load(std::string filename)
{
}
