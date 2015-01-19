/*
 * RelationshipType.cpp
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#include "RelationshipType.h"

RelationshipType::RelationshipType(std::string name, bool persist, bool synchronize, CefRefPtr<EntityType> startNodeType, CefRefPtr<EntityType> endNodeType)
    : TypeBase(name, persist, synchronize), startNodeType(startNodeType), endNodeType(endNodeType)
{
}

RelationshipType::~RelationshipType()
{
}

