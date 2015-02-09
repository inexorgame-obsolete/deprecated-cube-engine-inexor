/*
 * RandomPosition.cpp
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#include "RandomPosition.h"

namespace inexor {
namespace entity {
namespace particle {

RandomPosition::RandomPosition() : EntityFunction(INITIALIZER_RANDOM_VELOCITY_FUNCTION)
{
}

RandomPosition::~RandomPosition()
{
}

void RandomPosition::Execute(TimeStep time_step, EntityInstance* emitter_inst, EntityInstance* initializer_inst, EntityInstance* particle_inst)
{
    (*particle_inst)[POS]->vec3Val.add(vec(rndscale(20.0f) - 10.0f, rndscale(20.0f) - 10.0f, rndscale(20.0f)));
}

}
}
}
