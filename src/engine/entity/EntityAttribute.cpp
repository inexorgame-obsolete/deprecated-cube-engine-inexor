/*
 * EntityAttribute.cpp
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#include "EntityAttribute.h"
#include "TypeBase.h"
#include "EntityType.h"
#include "RelationshipType.h"
#include "EntityInstance.h"
#include "RelationshipInstance.h"

void EntityAttribute::operator()()
{
    if (this->type == ENTATTR_FUNCTION) {
        functionVal();
    }
}

void EntityAttribute::operator()(TypeBase* type)
{
    if (this->type == ENTATTR_FUNCTION) {
        functionVal(type);
    }
}

void EntityAttribute::operator()(EntityType* type)
{
    if (this->type == ENTATTR_FUNCTION) {
        functionVal(type);
    }
}

void EntityAttribute::operator()(RelationshipType* type)
{
    if (this->type == ENTATTR_FUNCTION) {
        functionVal(type);
    }
}

void EntityAttribute::operator()(EntityInstance* inst)
{
    if (this->type == ENTATTR_FUNCTION) {
        functionVal(inst);
    }
}

void EntityAttribute::operator()(RelationshipInstance* inst)
{
    if (this->type == ENTATTR_FUNCTION) {
        functionVal(inst);
    }
}

void AttributeRefPtr::operator()()
{
    get()->functionVal();
}

void AttributeRefPtr::operator()(TypeBase* type)
{
    get()->functionVal(type);
}

void AttributeRefPtr::operator()(EntityType* type)
{
    get()->functionVal(type);
}

void AttributeRefPtr::operator()(RelationshipType* type)
{
    get()->functionVal(type);
}

void AttributeRefPtr::operator()(EntityInstance* inst)
{
    get()->functionVal(inst);
}

void AttributeRefPtr::operator()(RelationshipInstance* inst)
{
    get()->functionVal(inst);
}
