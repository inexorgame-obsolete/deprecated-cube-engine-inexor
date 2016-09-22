/*
 * PulseInitializer.cpp
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#include "../operator/IncreaseInteger.hpp"

namespace inexor {
namespace vscript {

    IncreaseInteger::IncreaseInteger() : EntityFunction(ENT_FUNC_INCREASE_INTEGER)
    {
    }

    IncreaseInteger::~IncreaseInteger()
    {
    }

    void IncreaseInteger::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> activator_instance, std::shared_ptr<EntityInstance> integer_memory_instance, std::shared_ptr<RelationshipInstance> activates)
    {
    	int value = integer_memory_instance->GetAttribute("value")->intVal++;
    }

}
}
