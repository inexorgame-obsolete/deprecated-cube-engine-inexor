/*
 * EntitySystem.cpp
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#include "EntitySystem.h"

#include "provider/TeleportEntityTypeProvider.h"

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
    subsystems[teleport_subsystem->GetName()] = teleport_subsystem;
    subsystems[particle_subsystem->GetName()] = particle_subsystem;

// === TESTS: Subsystems ===

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

    for (int i = 0; i < 5; i++)
    {
        std::string particle_type_name = "default_particle_" + i;
        std::string particle_emitter_type_name = "simple_emitter_" + i;
        TypeRefPtr<EntityType> default_particle_type = particle_subsystem->CreateParticleType(particle_type_name);
        TypeRefPtr<EntityType> simple_particle_emitter_type = particle_subsystem->CreateParticleEmitterType(particle_emitter_type_name);
    }

    logoutf("Entity: Types: %d Instances: %d", entity_type_manager->Size(), entity_instance_manager->Size());
    logoutf("Relationships: Types: %d Instances: %d", relationship_type_manager->Size(), relationship_instance_manager->Size());


// === TESTS: Attributes ===

    // Entity Attribute Test Cases

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
    logoutf("test 14: type: %d expected: %s value: %s", et["function1"]->GetType(), "test", et["function1"]->GetFunction()->GetName().c_str());
    et["function2"] = (FunctionRefPtr) new EntityFunction("action2");
    logoutf("test 15: type: %d expected: %s value: %s", et["function2"]->GetType(), "test", et["function2"]->GetFunction()->GetName().c_str());
    et["function2"]->GetFunction()->Execute();
    et["function2"]->GetFunction()->Execute(et);
    et["function2"]->operator ()();
    et["function2"]->operator ()(et);
    et["function2"]();
    et["function2"](et);
    InstanceRefPtr<EntityInstance> ei = new EntityInstance(et);
    ei["x"] = 10.0;
    logoutf("test 16: type: %s name: %s type: %d expected: %3f value: %3f", ei->GetType()->GetName().c_str(), ei["x"]->name.c_str(), ei["x"]->type, 10.0, ei["x"]->GetDouble());
    ei["y"] = -10.0;
    logoutf("test 17: type: %s name: %s type: %d expected: %3f value: %3f", ei->GetType()->GetName().c_str(), ei["y"]->name.c_str(), ei["x"]->type, -10.0, ei["y"]->GetDouble());


/*
    InstanceRefPtr<EntityInstance> teleport1 = entity_instance_manager->Create(teleport_provider->GetEntityType());
    teleport1["x"] = 1;
    InstanceRefPtr<EntityInstance> teledest1 = entity_instance_manager->Create(teledest_provider->GetEntityType());
    teledest1["x"] = 1;

    InstanceRefPtr<RelationshipInstance> teleporting1 = relationship_instance_manager->CreateInstance(teleporting_provider->GetRelationshipType(), teleport1, teledest1);
*/

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

/*
    TypeRefPtr<EntityType> et_teleport = new EntityType(ENTTYPE_TELEPORT, true, true);
    TypeRefPtr<EntityType> et_teledest = new EntityType(ENTTYPE_TELEDEST, true, true);

    TypeRefPtr<RelationshipType> teleports_to = new RelationshipType(RELTYPE_TELEPORTS_TO, true, true, et_teleport, et_teledest);
    teleports_to["teleport"] = (FunctionRefPtr) new EntityFunction();
    teleports_to["teleport"]();

    InstanceRefPtr<EntityInstance> ei_teleporter_1 = new EntityInstance(et_teleport);
    InstanceRefPtr<EntityInstance> ei_teleporter_2 = new EntityInstance(et_teleport);

    InstanceRefPtr<EntityInstance> ei_teledest_1 = new EntityInstance(et_teledest);
    InstanceRefPtr<EntityInstance> ei_teledest_2 = new EntityInstance(et_teledest);
    InstanceRefPtr<EntityInstance> ei_teledest_3 = new EntityInstance(et_teledest);

    InstanceRefPtr<RelationshipInstance> ri_is_target_1_1 = new RelationshipInstance(teleports_to, ei_teleporter_1, ei_teledest_1);
    InstanceRefPtr<RelationshipInstance> ri_is_target_1_3 = new RelationshipInstance(teleports_to, ei_teleporter_1, ei_teledest_3);
    InstanceRefPtr<RelationshipInstance> ri_is_target_2_2 = new RelationshipInstance(teleports_to, ei_teleporter_2, ei_teledest_2);
    InstanceRefPtr<RelationshipInstance> ri_is_target_2_3 = new RelationshipInstance(teleports_to, ei_teleporter_2, ei_teledest_3);
*/

}

void EntitySystem::Save(std::string filename)
{
}

void EntitySystem::Load(std::string filename)
{
}
