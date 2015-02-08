/*
 * PulseInitializer.cpp
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#include "RandomVelocity.h"

namespace inexor {
namespace entity {
namespace particle {

RandomVelocity::RandomVelocity() : EntityFunction(INITIALIZER_RANDOM_VELOCITY_FUNCTION)
{
}

RandomVelocity::~RandomVelocity()
{
}

void RandomVelocity::Execute(TimeStep time_step, EntityInstance* emitter_inst, EntityInstance* initializer_inst, EntityInstance* particle_inst)
{
    (*particle_inst)[VELOCITY]->vec3Val = vec(rndscale(20.0f) - 10.0f, rndscale(20.0f) - 10.0f, rndscale(20.0f));
}

}
}
}
