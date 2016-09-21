/*
 * Immortal.cpp
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#include "Immortal.hpp"

namespace inexor {
namespace entity {
namespace particle {

    Immortal::Immortal() : EntityFunction(MODIFIER_IMMORTAL_FUNCTION)
    {
    }

    Immortal::~Immortal()
    {
    }

    void Immortal::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> modifier, std::shared_ptr<EntityInstance> particle)
    {
        (*particle)[REMAINING]->intVal = RAND_MAX;
    }

}
}
}
