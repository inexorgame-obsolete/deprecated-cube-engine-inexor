/*
 * EntityTypeProvider.cpp
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#include "EntityTypeProvider.hpp"
#include "../manager/EntityTypeManager.hpp"

namespace inexor {
namespace entity {

EntityTypeProvider::EntityTypeProvider(std::string entity_name) : entity_name(entity_name) {}
EntityTypeProvider::~EntityTypeProvider() {}

std::string EntityTypeProvider::GetEntityName()
{
    return entity_name;
}

TypeRefPtr<EntityType> EntityTypeProvider::GetEntityType()
{
    return entity_type;
}

}
}
