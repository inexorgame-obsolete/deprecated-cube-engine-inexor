/*
 * Culling.cpp
 *
 *  Created on: 15.02.2015
 *      Author: aschaeffer
 */

#include "Culling.hpp"

namespace inexor {
namespace entity {
namespace particle {

    Culling::Culling() : EntityFunction(MODIFIER_IMMORTAL_FUNCTION)
    {
    }

    Culling::~Culling()
    {
    }

    void Culling::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> modifier, std::shared_ptr<EntityInstance> particle)
    {
        // Immediately kill the particle
        (*particle)[REMAINING]->intVal = 0;
    }

}
}
}
