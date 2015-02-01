/*
 * Entity.h
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYINSTANCE_H_
#define SRC_ENGINE_ENTITY_ENTITYINSTANCE_H_

#include "../../EntitySystemBase.h"
#include "../InstanceBase.h"
#include "../TypeRefPtr.h"
#include "../InstanceRefPtr.h"
#include "EntityType.h"

class RelationshipInstance;

class EntityInstance : public InstanceBase
{
    public:
        EntityInstance(TypeRefPtr<EntityType> type);
        EntityInstance(TypeRefPtr<EntityType> type, std::string uuid);
        virtual ~EntityInstance();

        /**
         * Returns the entity type for this entity instance.
         */
        TypeRefPtr<EntityType> GetType();

        /**
         * Adds an outgoing relationship. This instance is the start node for
         * the created relation.
         */
        void AddOutgoingRelationship(TypeRefPtr<RelationshipType> relationship_type, InstanceRefPtr<RelationshipInstance> relationship_instance);

        /**
         * Adds an incoming relationship. This instance is the end node for
         * the created relation.
         */
        void AddIncomingRelationship(TypeRefPtr<RelationshipType> relationship_type, InstanceRefPtr<RelationshipInstance> relationship_instance);

        /**
         * Returns all relationships (incoming and outgoing).
         */
        std::list<InstanceRefPtr<RelationshipInstance> > GetAllRelationships();

        /**
         * Returns all relationships of the given relationship type.
         */
        std::list<InstanceRefPtr<RelationshipInstance> > GetRelationshipsOfType(TypeRefPtr<RelationshipType> relationship_type);

        /**
         * Returns all outgoing relationships.
         */
        std::list<InstanceRefPtr<RelationshipInstance> > GetAllOutgoingRelationships();

        /**
         * Returns all outgoing relationships of the given relationship type.
         */
        std::list<InstanceRefPtr<RelationshipInstance> > GetAllOutgoingRelationshipsOfType(TypeRefPtr<RelationshipType> relationship_type);

        /**
         * Returns all incoming relationships.
         */
        std::list<InstanceRefPtr<RelationshipInstance> > GetAllIncomingRelationships();

        /**
         * Returns all incoming relationships of the given relationship type.
         */
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

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityInstance);

};

#endif /* SRC_ENGINE_ENTITY_ENTITYINSTANCE_H_ */
