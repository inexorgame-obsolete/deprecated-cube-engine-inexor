/*
 * VelocityTransformation.cpp
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#include "VelocityTransformation.hpp"

namespace inexor {
namespace entity {
namespace particle {

    VelocityTransformation::VelocityTransformation() : EntityFunction(MODIFIER_VELOCITY_TRANSFORMATION_FUNCTION)
    {
    }

    VelocityTransformation::~VelocityTransformation()
    {
    }

    void VelocityTransformation::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> modifier, std::shared_ptr<EntityInstance> particle)
    {
        // Store last position
        (*particle)[LAST_POS]->vec3Val = (*particle)[POS]->vec3Val;
        // Add velocity vector
        (*particle)[POS]->vec3Val.add(vec((*particle)[VELOCITY]->vec3Val).mul(time_step.time_factor));
    }

}
}
}
