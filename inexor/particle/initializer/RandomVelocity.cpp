/*
 * PulseInitializer.cpp
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#include "RandomVelocity.hpp"

namespace inexor {
namespace entity {
namespace particle {

    RandomVelocity::RandomVelocity() : EntityFunction(INITIALIZER_RANDOM_VELOCITY_FUNCTION)
    {
    }

    RandomVelocity::~RandomVelocity()
    {
    }

    void RandomVelocity::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> emitter_inst, std::shared_ptr<EntityInstance> initializer_inst, std::shared_ptr<EntityInstance> particle_inst)
    {
        vec d = (*initializer_inst)[DELTA]->vec3Val;
        (*particle_inst)[VELOCITY]->vec3Val = vec(rndscale(d.x * 2.0f) - d.x, rndscale(d.y * 2.0f) - d.y, rndscale(d.z * 2.0f) - d.z);
    }

}
}
}
