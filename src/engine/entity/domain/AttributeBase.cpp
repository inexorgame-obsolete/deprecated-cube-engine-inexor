/*
 * AttributeBase.cpp
 *
 *  Created on: 18.01.2015
 *      Author: aschaeffer
 */

#include "AttributeBase.h"
#include "AttributeRefPtr.h"
#include "FunctionRefPtr.h"

AttributeBase::AttributeBase()
{
}

AttributeBase::~AttributeBase()
{
}

AttributeRefPtr AttributeBase::GetAttribute(std::string key)
{
    return attributes[key];
}

void AttributeBase::SetAttribute(std::string key, AttributeRefPtr attributeRefPtr)
{
    attributes[key] = attributeRefPtr;
}

bool AttributeBase::HasAttribute(std::string key)
{
    return attributes.count(key);
}

AttributeRefPtr AttributeBase::operator[](std::string key) const
{
    return attributes.find(key)->second;
}

AttributeRefPtr & AttributeBase::operator[](std::string key)
{
    return attributes[key];
}

void AttributeBase::AddAttribute(std::string key, AttributeRefPtr attribute)
{
    attribute.get()->name = key;
    attribute.get()->initialized = true;
    attributes[key] = attribute;
}

void AttributeBase::AddAttribute(std::string key, bool value)
{
    attributes[key] = value;
    attributes[key]->type = value;
    attributes[key]->name = key;
    attributes[key]->initialized = true;
}

void AttributeBase::AddAttribute(std::string key, int value)
{
    attributes[key] = value;
    attributes[key]->type = ENTATTR_INT;
    attributes[key]->name = key;
    attributes[key]->initialized = true;
}

void AttributeBase::AddAttribute(std::string key, float value)
{
    attributes[key] = value;
    attributes[key]->type = ENTATTR_FLOAT;
    attributes[key]->name = key;
    attributes[key]->initialized = true;
}

void AttributeBase::AddAttribute(std::string key, double value)
{
    attributes[key] = value;
    attributes[key]->type = ENTATTR_DOUBLE;
    attributes[key]->name = key;
    attributes[key]->initialized = true;
}

void AttributeBase::AddAttribute(std::string key, std::string value)
{
    attributes[key] = value;
    attributes[key]->type = ENTATTR_STRING;
    attributes[key]->name = key;
    attributes[key]->initialized = true;
}

void AttributeBase::AddAttribute(std::string key, FunctionRefPtr action)
{
    attributes[key] = action;
    attributes[key]->type = ENTATTR_FUNCTION;
    attributes[key]->name = key;
    attributes[key]->initialized = true;
}
