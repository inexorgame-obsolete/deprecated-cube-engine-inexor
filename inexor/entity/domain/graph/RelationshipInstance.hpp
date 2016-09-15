/*
 * Relationship.h
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_RELATIONSHIPINSTANCE_H_
#define SRC_ENGINE_ENTITY_RELATIONSHIPINSTANCE_H_

#include "../../EntitySystemBase.hpp"
#include "../InstanceBase.hpp"
#include "EntityInstance.hpp"
#include "EntityAttribute.hpp"
#include "RelationshipType.hpp"

namespace inexor {
namespace entity {

    class EntityInstance;

    /**
     * Represents an relationship instance between two entity instances (the start
     * and the end node). The relationship instance is of an relationship type.
     */
    class RelationshipInstance : public InstanceBase
    {
        public:

            /**
             * Constructs a new relationship of the given type with the given start
             * node and end node entity instances.
             *
             * A new unique identifier is created automatically.
             *
             * @param type The relationship type.
             * @param startNode The start node entity instance.
             * @param endNode The end node entity instance.
             */
            RelationshipInstance(TypeRefPtr<RelationshipType> type, InstanceRefPtr<EntityInstance> startNode, InstanceRefPtr<EntityInstance> endNode);

            /**
             * Constructs a new relationship of the given type with the given start
             * node and end node entity instances.
             *
             * The uuid represents the unique identifier of the relationship
             * instance. The uuid is known, if the relationship instance is loaded
             * from file or synchronized from network.
             *
             * @param type The relationship type.
             * @param startNode The start node entity instance.
             * @param endNode The end node entity instance.
             * @param uuid The uuid of the relationship instance.
             */
            RelationshipInstance(TypeRefPtr<RelationshipType> type, InstanceRefPtr<EntityInstance> startNode, InstanceRefPtr<EntityInstance> endNode, std::string uuid);
            virtual ~RelationshipInstance();

            /**
             * Returns the relationship type of this relationship instance.
             * @return The relationship type.
             */
            TypeRefPtr<RelationshipType> GetType();

            /**
             * Returns the start node entity instance of this relationship.
             * @return The start node entity instance.
             */
            InstanceRefPtr<EntityInstance> GetStartNode();

            /**
             * Returns the end node entity instance of this relationship.
             * @return The end node entity instance.
             */
            InstanceRefPtr<EntityInstance> GetEndNode();

            /**
             * The start node (parent node) is an entity instance.
             * Because of performance reasons, this is public.
             */
            InstanceRefPtr<EntityInstance> startNode;

            /**
             * The end node (child node) is an entity instance.
             * Because of performance reasons, this is public.
             */
            InstanceRefPtr<EntityInstance> endNode;

            /**
             * If not alive, remove this element at next iteration.
             */
            bool alive;

            /**
             * The relationship type.
             */
            TypeRefPtr<RelationshipType> type;

        protected:

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(RelationshipInstance);

    };

}
}

#endif /* SRC_ENGINE_ENTITY_RELATIONSHIPINSTANCE_H_ */
