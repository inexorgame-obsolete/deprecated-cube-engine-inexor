/*
 * EntityType.cpp
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#include "EntityType.h"

namespace inexor {
namespace entity {

EntityType::EntityType(std::string name, bool persist, bool synchronize) : TypeBase(name, persist, synchronize)
{
}

EntityType::EntityType(std::string name, bool persist, bool synchronize, TypeRefPtr<EntityType> parent) : TypeBase(name, persist, synchronize), parent(parent)
{
}

bool EntityType::IsA(TypeRefPtr<EntityType> type)
{
    return this->uuid == type->uuid || (parent.get() && parent->uuid == type->uuid);
}

bool EntityType::IsA(std::string uuid)
{
    return this->uuid == uuid || (parent.get() && parent->uuid == uuid);
}

bool EntityType::IsExactlyA(TypeRefPtr<EntityType> type)
{
    return this->uuid == type->uuid;
}

bool EntityType::IsExactlyA(std::string uuid)
{
    return this->uuid == uuid;
}

}
}
