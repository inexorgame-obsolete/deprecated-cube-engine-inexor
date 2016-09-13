/*
 * InstanceBase.cpp
 *
 *  Created on: 18.01.2015
 *      Author: aschaeffer
 */

#include "InstanceBase.h"

namespace inexor {
namespace entity {

InstanceBase::InstanceBase()
{
    // Generate UUID
    // uuid::Uuid u = uuid::uuid1((uint64_t) 0x19432987, (uint16_t) 0x33);
    // std::pair<uint64_t, uint64_t> p = u.integer();
    uuid::Uuid u = uuid::uuid1();
    uuid = u.hex();
}

InstanceBase::InstanceBase(std::string uuid) : uuid(uuid)
{
}

InstanceBase::~InstanceBase()
{
}

std::string InstanceBase::GetUuid()
{
    return uuid;
}

void InstanceBase::SetUuid(std::string uuid)
{
    this->uuid = uuid;
}

}
}
