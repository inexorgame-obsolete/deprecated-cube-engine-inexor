/*
 * RelationshipType.cpp
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#include "RelationshipType.h"

RelationshipType::RelationshipType(std::string name, bool persist, bool synchronize)
    : TypeBase(name, persist, synchronize)
{
}

RelationshipType::~RelationshipType()
{
    // TODO Auto-generated destructor stub
}

