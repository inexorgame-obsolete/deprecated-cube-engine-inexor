/*
 * EntityTest.cpp
 *
 *  Created on: 14.02.2015
 *      Author: aschaeffer
 */

#include "EntityTest.hpp"

namespace inexor {
namespace entity {

    EntityTest::EntityTest()
    {
    }

    EntityTest::~EntityTest()
    {
    }

    void EntityTest::RunTests()
    {
        SubsystemTest();
        InstanceCreationTest();
        LowLevelTypeCreationTest();
        TypeCreationTest();
        AttributeTest();
    }

    void EntityTest::CleanupTests()
    {
        entity_system->Cleanup();
    }

    void EntityTest::SubsystemTest()
    {
        logoutf("Try to access subsystems by type");
        CefRefPtr<TeleportSubsystem> teleport_subsystem = entity_system->GetSubsystem<TeleportSubsystem>();
        CefRefPtr<inexor::entity::particle::ParticleSubsystem> particle_subsystem = entity_system->GetSubsystem<inexor::entity::particle::ParticleSubsystem>();
    }

    void EntityTest::InstanceCreationTest()
    {
        logoutf("Creating 100000 entity and 100000 relationship instances");
        CefRefPtr<TeleportSubsystem> teleport_subsystem = entity_system->GetSubsystem<TeleportSubsystem>();
        InstanceRefPtr<EntityInstance> teleport1 = teleport_subsystem->CreateTeleport(0.0, 0.0, 0.0);
        InstanceRefPtr<EntityInstance> teledest1 = teleport_subsystem->CreateTeledest(0.0, 0.0, 0.0);
        InstanceRefPtr<RelationshipInstance> teleporting1 = teleport_subsystem->Connect(teleport1, teledest1);
        for (int i = 0; i < 100000; i++)
        {
            InstanceRefPtr<EntityInstance> teledest = teleport_subsystem->CreateTeledest(0.0, 0.0, 0.0);
            InstanceRefPtr<RelationshipInstance> teleporting = teleport_subsystem->Connect(teleport1, teledest);
        }
        PrintStats();
    }

    void EntityTest::LowLevelTypeCreationTest()
    {
        logoutf("Create entity and relationship types (low level)");
        TypeRefPtr<EntityType> source_type = entity_system->GetEntityTypeManager()->Create("source_type", false, false);
        TypeRefPtr<EntityType> target_type = entity_system->GetEntityTypeManager()->Create("target_type", false, false);
        TypeRefPtr<RelationshipType> relationship_type = entity_system->GetRelationshipTypeManager()->Create("relationship_type", false, false, source_type, target_type);
        PrintStats();
    }

    void EntityTest::TypeCreationTest()
    {
        logoutf("Create a batch of entity types");
        CefRefPtr<inexor::entity::particle::ParticleSubsystem> particle_subsystem = entity_system->GetSubsystem<inexor::entity::particle::ParticleSubsystem>();
        for (int i = 0; i < 1000; i++)
        {
            std::string particle_type_name = "default_particle_" + i;
            std::string particle_emitter_type_name = "simple_emitter_" + i;
            std::string test_function_name = "test_function_" + i;
            FunctionRefPtr test_function_i = new EntityFunction(test_function_name);
            TypeRefPtr<EntityType> particle_type_i = particle_subsystem->CreateParticleType(particle_type_name, "default_renderer");
            TypeRefPtr<EntityType> particle_emitter_type_i = particle_subsystem->CreateEmitterType(particle_emitter_type_name, test_function_i, particle_type_i, 100, 1, 1000, 0.1, 1.0);
        }
        PrintStats();
    }

    void EntityTest::AttributeTest()
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

    void EntityTest::PrintStats()
    {
        logoutf("Entity: Types: %3d Instances: %6d Relationships: Types: %3d Instances: %6d", entity_system->GetEntityTypeManager()->Size(), entity_system->GetEntityInstanceManager()->Size(), entity_system->GetRelationshipTypeManager()->Size(), entity_system->GetRelationshipInstanceManager()->Size());
    }

}
}
