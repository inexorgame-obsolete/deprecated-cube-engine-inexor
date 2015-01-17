/*
 * EntityAttribute.cpp
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#include "EntityAttribute.h"

EntityAttribute::EntityAttribute(int type, std::string name, void* value) : type(type), name(name), value(value)
{

}

EntityAttribute::~EntityAttribute()
{
    // TODO Auto-generated destructor stub
}

void EntityAttribute::SetType(int type) { this->type = type; };
int EntityAttribute::GetType() { return type; };
void EntityAttribute::SetValue(void* value) { this->value = value; };
void* EntityAttribute::GetValue() { return value; };
