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
    (*particle_inst)[VELOCITY]->vec3Val = vec(rndscale(5.0f), rndscale(5.0f), rndscale(5.0f));
    logoutf("set random velocity: ( %2.2f, %2.2f, %2.2f )",
        (*particle_inst)[VELOCITY]->vec3Val.x, (*particle_inst)[VELOCITY]->vec3Val.y, (*particle_inst)[VELOCITY]->vec3Val.z
    );

}

}
}
}
