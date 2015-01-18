/*
 * EntitySystem.cpp
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#include "EntitySystem.h"

EntitySystem::EntitySystem()
{

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
    FunctionRefPtr entAction = new EntityFunction();
    et["function1"] = entAction;
    logoutf("test 14: type: %d expected: %s value: %s", et["function1"]->GetType(), "test", et["function1"]->GetFunction()->GetName().c_str());
    et["function2"] = (FunctionRefPtr) new EntityFunction();
    logoutf("test 15: type: %d expected: %s value: %s", et["function2"]->GetType(), "test", et["function2"]->GetFunction()->GetName().c_str());
    // et["function2"]->

}

EntitySystem::~EntitySystem()
{
}

CefRefPtr<EntityType> EntitySystem::CreateEntityType(std::string name, bool persist, bool synchronize)
{
    CefRefPtr<EntityType> entity_type = new EntityType(name, persist, synchronize);
    entity_types[name] = entity_type;
    return entity_type;
}

CefRefPtr<RelationshipType> EntitySystem::CreateRelationshipType(std::string name, bool persist, bool synchronize)
{
    CefRefPtr<RelationshipType> relationship_type = new RelationshipType(name, persist, synchronize);
    relationship_types[name] = relationship_type;
    return relationship_type;
}

CefRefPtr<EntityType> EntitySystem::GetEntityType(std::string name)
{
    return entity_types[name];
}

CefRefPtr<RelationshipType> EntitySystem::GetRelationshipType(std::string name)
{
    return relationship_types[name];
}


