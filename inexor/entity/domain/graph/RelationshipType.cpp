/*
 * RelationshipType.cpp
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#include "RelationshipType.hpp"

namespace inexor {
namespace entity {

    RelationshipType::RelationshipType(std::string name,
                                       bool persist,
                                       bool synchronize,
                                       TypeRefPtr<EntityType> startNodeType,
                                       TypeRefPtr<EntityType> endNodeType)
        : TypeBase(name,persist, synchronize), start_node_type(startNodeType), end_node_type(endNodeType)
    {
    }

    RelationshipType::~RelationshipType()
    {
    }

}
}
