/*
 * InstanceBase.cpp
 *
 *  Created on: 18.01.2015
 *      Author: aschaeffer
 */

#include "InstanceBase.hpp"

namespace inexor {
namespace entity {

    InstanceBase::InstanceBase()
    {
        // Generate UUID
        random_generator gen;
        uuid = boost::lexical_cast<std::string>(gen());
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
