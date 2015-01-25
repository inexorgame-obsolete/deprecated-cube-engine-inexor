/*
 * Entity.h
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYINSTANCE_H_
#define SRC_ENGINE_ENTITY_ENTITYINSTANCE_H_

#include "EntitySystemBase.h"
#include "InstanceBase.h"

#include "EntityAttribute.h"
#include "EntityType.h"

class RelationshipInstance;

class EntityInstance : public InstanceBase
{
    public:
        EntityInstance(TypeRefPtr<EntityType> type);
        EntityInstance(TypeRefPtr<EntityType> type, std::string uuid);
        virtual ~EntityInstance();

        TypeRefPtr<EntityType> GetType() { return type; };

        void AddOutgoingRelationship(TypeRefPtr<RelationshipType> relationship_type, InstanceRefPtr<RelationshipInstance> relationship_instance);
        void AddIncomingRelationship(TypeRefPtr<RelationshipType> relationship_type, InstanceRefPtr<RelationshipInstance> relationship_instance);

        std::list<InstanceRefPtr<RelationshipInstance> > GetAllRelationships();
        std::list<InstanceRefPtr<RelationshipInstance> > GetRelationshipsOfType(TypeRefPtr<RelationshipType> relationship_type);
        std::list<InstanceRefPtr<RelationshipInstance> > GetAllOutgoingRelationships();
        std::list<InstanceRefPtr<RelationshipInstance> > GetAllOutgoingRelationshipsOfType(TypeRefPtr<RelationshipType> relationship_type);
        std::list<InstanceRefPtr<RelationshipInstance> > GetAllIncomingRelationships();
        std::list<InstanceRefPtr<RelationshipInstance> > GetAllIncomingRelationshipsOfType(TypeRefPtr<RelationshipType> relationship_type);

    protected:

        /**
         * The entity type.
         */
        TypeRefPtr<EntityType> type;

        /**
         * The child relationships by type (this instance is the start node).
         */
        std::map<TypeRefPtr<RelationshipType>, std::list<InstanceRefPtr<RelationshipInstance> > > outgoing;

        /**
         * The parent relationships by type (this instance is the end node).
         */
        std::map<TypeRefPtr<RelationshipType>, std::list<InstanceRefPtr<RelationshipInstance> > > incoming;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityInstance);

};

#endif /* SRC_ENGINE_ENTITY_ENTITYINSTANCE_H_ */
