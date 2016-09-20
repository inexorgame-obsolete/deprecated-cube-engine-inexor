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
        LowLevelTypeCreationTest();
        LowLevelInstanceCreationTest();
        // InstanceCreationTest();
        TypeCreationTest();
        AttributeTest();
    }

    void EntityTest::CleanupTests()
    {
        entity_system->Cleanup();
    }

    void EntityTest::SubsystemTest()
    {
        spdlog::get("global")->info() << "Try to access subsystems by type";
        // std::shared_ptr<TeleportSubsystem> teleport_subsystem = entity_system->GetSubsystem<TeleportSubsystem>();
        // std::shared_ptr<inexor::entity::particle::ParticleSubsystem> particle_subsystem = entity_system->GetSubsystem<inexor::entity::particle::ParticleSubsystem>();
    }

    void EntityTest::InstanceCreationTest()
    {
        spdlog::get("global")->info() << "Creating 100000 entity and 100000 relationship instances";
        // std::shared_ptr<TeleportSubsystem> teleport_subsystem = entity_system->GetSubsystem<TeleportSubsystem>();
        // InstanceRefPtr<EntityInstance> teleport1 = teleport_subsystem->CreateTeleport(0.0, 0.0, 0.0);
        // InstanceRefPtr<EntityInstance> teledest1 = teleport_subsystem->CreateTeledest(0.0, 0.0, 0.0);
        // InstanceRefPtr<RelationshipInstance> teleporting1 = teleport_subsystem->Connect(teleport1, teledest1);
        // for (int i = 0; i < 100000; i++)
        // {
        // InstanceRefPtr<EntityInstance> teledest = teleport_subsystem->CreateTeledest(0.0, 0.0, 0.0);
        // InstanceRefPtr<RelationshipInstance> teleporting = teleport_subsystem->Connect(teleport1, teledest);
        // }
        // PrintStats();
    }

    void EntityTest::LowLevelTypeCreationTest()
    {
        spdlog::get("global")->info() << "Create entity and relationship types (low level)";
        TypeRefPtr<EntityType> source_type = entity_system->GetEntityTypeManager()->Create("source_type", false, false);
        TypeRefPtr<EntityType> target_type = entity_system->GetEntityTypeManager()->Create("target_type", false, false);
        TypeRefPtr<RelationshipType> relationship_type = entity_system->GetRelationshipTypeManager()->Create("relationship_type", false, false, source_type, target_type);
        PrintStats();
    }

    void EntityTest::LowLevelInstanceCreationTest()
    {
        spdlog::get("global")->info() << "Create entity and relationship types (low level)";
        TypeRefPtr<EntityType> source_type = entity_system->GetEntityTypeManager()->Get("source_type");
        InstanceRefPtr<EntityInstance> source_instance_1 = entity_system->GetEntityInstanceManager()->Create(source_type);
        PrintStats();
    }

    void EntityTest::TypeCreationTest()
    {
    	spdlog::get("global")->info() << "Create a batch of entity types";
        // std::shared_ptr<inexor::entity::particle::ParticleSubsystem> particle_subsystem = entity_system->GetSubsystem<inexor::entity::particle::ParticleSubsystem>();
        // for (int i = 0; i < 1000; i++)
        // {
        // std::string particle_type_name = "default_particle_" + i;
        // std::string particle_emitter_type_name = "simple_emitter_" + i;
        // std::string test_function_name = "test_function_" + i;
        // FunctionRefPtr test_function_i = std::make_shared<EntityFunction>(test_function_name);
        // TypeRefPtr<EntityType> particle_type_i = particle_subsystem->CreateParticleType(particle_type_name, "default_renderer");
        // TypeRefPtr<EntityType> particle_emitter_type_i = particle_subsystem->CreateEmitterType(particle_emitter_type_name, test_function_i, particle_type_i, 100, 1, 1000, 0.1, 1.0);
        // }
        // PrintStats();
    }

    void EntityTest::AttributeTest()
    {
        spdlog::get("global")->info() << "Test attributes";
        AttributeRefPtr attr_int_1 = std::make_shared<EntityAttribute>(1);
        spdlog::get("global")->info() << "test  1: type: " << attr_int_1->GetType() << " expected: " << 1 << " value: " << attr_int_1->GetInteger();
        AttributeRefPtr attr_int_2 = 2;
        spdlog::get("global")->info() << "test  2: type: " << attr_int_2->GetType() << " expected: " << 2 << " value: " << attr_int_2->GetInteger();
        TypeRefPtr<EntityType> et = std::make_shared<EntityType>("et1", false, false);
        et->AddAttribute("int1", attr_int_1);
        spdlog::get("global")->info() << "test  3: type: " << et["int1"]->GetType() << " expected: " << 1 << " value: " << et["int1"]->GetInteger();
        et->AddAttribute("int2", attr_int_2);
        spdlog::get("global")->info() << "test  4: type: " << et["int2"]->GetType() << " expected: " << 2 << " value: " << et["int2"]->GetInteger();
        AttributeRefPtr attr_double_1 = 3.0;
        et->AddAttribute("double1", attr_double_1);
        spdlog::get("global")->info() << "test  5: type: " << et["double1"]->GetType() << " expected: 3.0 value: " << et["double1"]->GetDouble();
        spdlog::get("global")->info() << "test  6: type: " << et->GetAttribute("double1")->GetType() << " expected: 3.0 value: " << et->GetAttribute("double1")->GetDouble();
        et->AddAttribute("double2", 4.0);
        spdlog::get("global")->info() << "test  7: type: " << et["double2"]->GetType() << " expected: 4.0 value: " << et["double2"]->GetDouble();
        spdlog::get("global")->info() << "test  8: type: " << et->GetAttribute("double2")->GetType() << " expected: 4.0 value: " << et->GetAttribute("double2")->GetDouble();
        et["int3"] = 5;
        spdlog::get("global")->info() << "test  9: type: " << et["int3"]->GetType() << " expected: 5 value: " << et["int3"]->GetInteger();
        et["double3"] = 6.0;
        spdlog::get("global")->info() << "test 10: type: " << et["double3"]->GetType() << " expected: 6.0 value: " << et["double3"]->GetDouble();
        et["string1"] = std::string("string1");
        spdlog::get("global")->info() << "test 11: type: " << et["string1"]->GetType() << " expected: string1 value: " << et["string1"]->GetString().c_str();
        et["boolfalse"] = false;
        spdlog::get("global")->info() << "test 12: type: " << et["boolfalse"]->GetType() << " expected: 0 value: " << et["boolfalse"]->GetBool();
        et["booltrue"] = true;
        spdlog::get("global")->info() << "test 13: type: " << et["booltrue"]->GetType() << " expected: 1 value: " << et["booltrue"]->GetBool();
        FunctionRefPtr entAction = std::make_shared<EntityFunction>("action1");
        et["function1"] = entAction;
        spdlog::get("global")->info() << "test 14: type: " << et["function1"]->GetType() << " expected: action1 value: " << et["function1"]->GetFunction()->GetName().c_str();
        et["function2"] = (FunctionRefPtr) std::make_shared<EntityFunction>("action2");
        spdlog::get("global")->info() << "test 15: type: " << et["function2"]->GetType() << " expected: action2 value: " << et["function2"]->GetFunction()->GetName().c_str();
        TimeStep t(0, 1.0, 1.0);
        et["function2"]->GetFunction()->Execute(t);
        et["function2"]->GetFunction()->Execute(t, et);
        et["function2"]->operator ()(t);
        et["function2"]->operator ()(t, et);
        et["function2"](t);
        et["function2"](t, et);
        InstanceRefPtr<EntityInstance> ei = std::make_shared<EntityInstance>(et);
        ei["x"] = 10.0;
        spdlog::get("global")->info() << "test 16: type: " << ei->GetType()->GetName().c_str() << " name: " << ei["x"]->name.c_str() << " type: " << ei["x"]->type << " expected: 10.0 value: " << ei["x"]->GetDouble();
        ei["y"] = -10.0;
        spdlog::get("global")->info() << "test 17: type: " << ei->GetType()->GetName().c_str() << " name: " << ei["y"]->name.c_str() << " type: " << ei["x"]->type << " expected: -10.0 value: " << ei["y"]->GetDouble();
    }

    void EntityTest::PrintStats()
    {
        spdlog::get("global")->info() << "Entity: Types: " << entity_system->GetEntityTypeManager()->Size() << " Instances: " << entity_system->GetEntityInstanceManager()->Size() << " Relationships: Types: " << entity_system->GetRelationshipTypeManager()->Size() << " Instances: " << entity_system->GetRelationshipInstanceManager()->Size();
    }

}
}
