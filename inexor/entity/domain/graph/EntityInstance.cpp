/*
 * Entity.cpp
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#include "EntityInstance.hpp"
#include "RelationshipInstance.hpp"

namespace inexor {
namespace entity {

    EntityInstance::EntityInstance(TypeRefPtr<EntityType> type)
        : InstanceBase(), type(type)
    {
    }

    EntityInstance::EntityInstance(TypeRefPtr<EntityType> type, std::string uuid)
        : InstanceBase(uuid), type(type)
    {
    }

    EntityInstance::~EntityInstance()
    {
    }

    TypeRefPtr<EntityType> EntityInstance::GetType()
    {
        return type;
    }

    void EntityInstance::AddOutgoingRelationship(TypeRefPtr<RelationshipType> relationship_type, InstanceRefPtr<RelationshipInstance> relationship_instance)
    {
        // TODO: check first for key and create key if not exists!
        this->outgoing[relationship_type->uuid].push_back(relationship_instance);
    }

    void EntityInstance::AddIncomingRelationship(TypeRefPtr<RelationshipType> relationship_type, InstanceRefPtr<RelationshipInstance> relationship_instance)
    {
        // TODO: check first for key and create key if not exists!
        this->incoming[relationship_type->uuid].push_back(relationship_instance);
    }

    /*
    std::list<InstanceRefPtr<RelationshipInstance> > EntityInstance::GetRelationshipsOfType(TypeRefPtr<RelationshipType> relationship_type)
    {
        // TODO: implement
    }
    */

    std::list<InstanceRefPtr<RelationshipInstance> > EntityInstance::GetAllOutgoingRelationshipsOfType(TypeRefPtr<RelationshipType> relationship_type)
    {
        return outgoing[relationship_type->uuid];
    }

    std::list<InstanceRefPtr<RelationshipInstance> > EntityInstance::GetAllIncomingRelationshipsOfType(TypeRefPtr<RelationshipType> relationship_type)
    {
        return incoming[relationship_type->uuid];
    }

}
}
