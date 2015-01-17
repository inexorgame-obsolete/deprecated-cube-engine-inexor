/*
 * EntitySystem.cpp
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#include "EntitySystem.h"

EntitySystem::EntitySystem()
{
    // TODO Auto-generated constructor stub

}

EntitySystem::~EntitySystem()
{
    // TODO Auto-generated destructor stub
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


