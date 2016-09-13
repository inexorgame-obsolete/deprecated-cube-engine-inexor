/*
 * TypeBase.cpp
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#include "TypeBase.hpp"

namespace inexor {
namespace entity {

TypeBase::TypeBase(std::string name, bool persist, bool synchronize)
    : name(name),
      persist(persist),
      synchronize(synchronize)
{
    uuid::Uuid u = uuid::uuid1();
    uuid = u.hex();
}

TypeBase::TypeBase(std::string name, bool persist, bool synchronize, std::string uuid)
    : uuid(uuid),
      name(name),
      persist(persist),
      synchronize(synchronize)
{
}

TypeBase::~TypeBase()
{
}

std::string TypeBase::GetUuid()
{
    return uuid;
}

void TypeBase::SetUuid(std::string uuid) {
    this->uuid = uuid;
}

std::string TypeBase::GetName() {
    return name;
}

std::string TypeBase::GetParentType() {
    return parent_type;
}

bool TypeBase::IsPersisting() {
    return persist;
}

bool TypeBase::IsSynchronizing() {
    return synchronize;
}

}
}
