/*
 * Entity.cpp
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#include "EntityInstance.h"
#include "RelationshipInstance.h"

EntityInstance::EntityInstance(CefRefPtr<EntityType> type) : type(type)
{
}

EntityInstance::~EntityInstance()
{
}

