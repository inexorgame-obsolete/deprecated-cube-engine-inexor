/*
 * RelationshipType.cpp
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#include "RelationshipType.h"

RelationshipType::RelationshipType(std::string name, bool persist, bool synchronize)
    : name(name),
      persist(persist),
      synchronize(synchronize)
{
    uuid = "0";
}

RelationshipType::~RelationshipType()
{
    // TODO Auto-generated destructor stub
}

