/*
 * Entity.h
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYINSTANCE_H_
#define SRC_ENGINE_ENTITY_ENTITYINSTANCE_H_

#include "../../EntitySystemBase.hpp"
#include "../InstanceBase.hpp"
#include "../TypeRefPtr.hpp"
#include "../InstanceRefPtr.hpp"
#include "EntityType.hpp"

namespace inexor {
namespace entity {

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
         * Returns all relationships of the given relationship type.
         */
        // TODO: uncomment and implement
        //std::list<InstanceRefPtr<RelationshipInstance> > GetRelationshipsOfType(TypeRefPtr<RelationshipType> relationship_type);

        /**
         * Returns all outgoing relationships of the given relationship type.
         */
        std::list<InstanceRefPtr<RelationshipInstance> > GetAllOutgoingRelationshipsOfType(TypeRefPtr<RelationshipType> relationship_type);

        /**
         * Returns all incoming relationships of the given relationship type.
         */
        std::list<InstanceRefPtr<RelationshipInstance> > GetAllIncomingRelationshipsOfType(TypeRefPtr<RelationshipType> relationship_type);

        /**
         * The child relationships by type (this instance is the start node).
         * Because of performance aspects, this is public.
         */
        std::unordered_map<std::string, std::list<InstanceRefPtr<RelationshipInstance> > > outgoing;

        /**
         * The parent relationships by type (this instance is the end node).
         * Because of performance aspects, this is public.
         */
        std::unordered_map<std::string, std::list<InstanceRefPtr<RelationshipInstance> > > incoming;

        /**
         * The entity type.
         */
        TypeRefPtr<EntityType> type;

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityInstance);

};

}
}

#endif /* SRC_ENGINE_ENTITY_ENTITYINSTANCE_H_ */
