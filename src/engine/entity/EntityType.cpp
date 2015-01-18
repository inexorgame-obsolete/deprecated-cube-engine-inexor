/*
 * EntityType.cpp
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#include "EntityType.h"

EntityType::EntityType(std::string name, bool persist, bool synchronize)
    : TypeBase(name, persist, synchronize)
{
}

EntityType::~EntityType()
{
}
