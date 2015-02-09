/*
 * VelocityTransformation.cpp
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#include "VelocityTransformation.h"

namespace inexor {
namespace entity {
namespace particle {

VelocityTransformation::VelocityTransformation() : EntityFunction(MODIFIER_VELOCITY_TRANSFORMATION_FUNCTION)
{
}

VelocityTransformation::~VelocityTransformation()
{
}

void VelocityTransformation::Execute(TimeStep time_step, EntityInstance* modifier, EntityInstance* particle)
{
    // Store last position
    (*particle)[LAST_POS]->vec3Val = (*particle)[POS]->vec3Val;
    // Add velocity vector
    (*particle)[POS]->vec3Val.add(vec((*particle)[VELOCITY]->vec3Val).mul(time_step.time_factor));

    /*
    (*particle)["x"]->doubleVal = (*particle)["x"]->doubleVal + (*particle)["vx"]->doubleVal * time_step.time_factor;
    (*particle)["y"]->doubleVal = (*particle)["y"]->doubleVal + (*particle)["vy"]->doubleVal * time_step.time_factor;
    (*particle)["z"]->doubleVal = (*particle)["z"]->doubleVal + (*particle)["vz"]->doubleVal * time_step.time_factor;
    */

    // TODO: remove debug
    /*
    logoutf("VelocityTransformation::Execute type: %d ( %2.2f, %2.2f, %2.2f ) = ( %2.2f, %2.2f, %2.2f ) + ( ( %2.2f, %2.2f, %2.2f ) * %2.2f )",
            (*particle)[POS]->type,
            (*particle)[POS]->vec3Val.x, (*particle)[POS]->vec3Val.y, (*particle)[POS]->vec3Val.z,
            (*particle)[LAST_POS]->vec3Val.x, (*particle)[LAST_POS]->vec3Val.y, (*particle)[LAST_POS]->vec3Val.z,
            (*particle)[VELOCITY]->vec3Val.x, (*particle)[VELOCITY]->vec3Val.y, (*particle)[VELOCITY]->vec3Val.z,
            time_step.time_factor
    );
    */

}

}
}
}
