/*
 * RelationshipType.h
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_RELATIONSHIPTYPE_H_
#define SRC_ENGINE_ENTITY_RELATIONSHIPTYPE_H_

#include "../TypeBase.hpp"
#include "../TypeRefPtr.hpp"
#include "EntityType.hpp"

namespace inexor {
namespace entity {

    /**
     * Represents a specific type of relationships. The relationship type
     * basically describes what the valid entity types are on the start
     * and the end node.
     *
     * With the help of relationship types, you can ensure that the start
     * node and the end node of a relationship instance are of the correct
     * entity type.
     *
     * In order to create relationship instances, you have to define a
     * relationship type first.
     *
     * An entity type can have a parent entity type. If you create an
     * relationship type which start node entity type is a parent, all
     * child entity types are also valid.
     *
     * For example: The "modifies" relationship type describes, that a
     * particle modifier instance modifies a particle instance:
     *
     * modifier--[:modifies]-->particle
     *
     * There is a parent entity type "particle_modifier" and all particle
     * modifier entity types are child types.
     *
     * Also, there is a parent particle entity type "particle_type" and all
     * particle entity types are child type.
     *
     * The relationship type therefore describes a relationship between
     * two parent entity types, which allows flexibility, because you can
     * create different types of modifiers and particles. But it also
     * ensures constraints, because it must be a entity type which is a
     * child type of "particle_modifier" / "particle_type".
     */
    class RelationshipType : public TypeBase
    {
        public:

            /**
             * Constructs a new relationship type.
             * @param name The name of the relationship type.
             * @param persist If true, the relationship type will be persisted.
             * @param synchronize If true, the relationship type will be synchronized.
             * @param startNodeType The entity type of the start node. May be a parent entity type.
             * @param endNodeType The entity type of the end node. May be a parent entity type.
             */
            RelationshipType(std::string name, bool persist, bool synchronize, TypeRefPtr<EntityType> startNodeType, TypeRefPtr<EntityType> endNodeType);
            virtual ~RelationshipType();

            /**
             * Returns the entity type of the start node.
             * @return The entity type of the start node, which may be a parent entity type.
             */
            std::shared_ptr<EntityType> GetStartNodeType() { return this->start_node_type; };

            /**
             * Sets the entity type of the start node.
             * @param startNodeType The entity type of the start node.
             */
            void SetStartNodeType(std::shared_ptr<EntityType> startNodeType) { this->start_node_type = startNodeType; };

            /**
             * Returns the entity type of the end node.
             * @return The entity type of the end node, which may be a parent entity type.
             */
            std::shared_ptr<EntityType> GetEndNodeType() { return this->end_node_type; };

            /**
             * Sets the entity type of the end node.
             * @param startNodeType The entity type of the end node.
             */
            void SetEndNodeType(std::shared_ptr<EntityType> startNodeType) { this->end_node_type = end_node_type; };

            /**
             * The entity type of the start node.
             */
            TypeRefPtr<EntityType> start_node_type;

            /**
             * The entity type of the end node.
             */
            TypeRefPtr<EntityType> end_node_type;

        private:

            // TODO: remove?
            void operator()(EntityInstance* inst);
    };

}
}

#endif /* SRC_ENGINE_ENTITY_RELATIONSHIPTYPE_H_ */
