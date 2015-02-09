/*
 * Immortal.cpp
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#include "Immortal.h"

namespace inexor {
namespace entity {
namespace particle {

Immortal::Immortal() : EntityFunction("immortal")
{
}

Immortal::~Immortal()
{
}

void Immortal::Execute(TimeStep time_step, EntityInstance* modifier, EntityInstance* particle)
{
    (*particle)[REMAINING]->intVal = RAND_MAX;
}

}
}
}
