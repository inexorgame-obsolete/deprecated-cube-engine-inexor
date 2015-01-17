/*
 * EntityType.cpp
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#include "EntityType.h"

EntityType::EntityType(std::string name, bool persist, bool synchronize)
    : name(name),
      persist(persist),
      synchronize(synchronize)
{
    uuid = "0";
}

EntityType::~EntityType()
{
    // TODO Auto-generated destructor stub
}

