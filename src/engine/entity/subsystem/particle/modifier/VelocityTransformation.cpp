/*
 * VelocityTransformation.cpp
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#include "VelocityTransformation.h"

VelocityTransformation::VelocityTransformation() : EntityFunction("velocity_transformation")
{
}

VelocityTransformation::~VelocityTransformation()
{
}

void VelocityTransformation::Execute(TimeStep time_step, EntityInstance* modifier, EntityInstance* particle)
{
    // TODO: too verbose (due to pointers instead of RefPtrs)

    // Store last position
    // EntityInstance i = (*particle);
    (*particle)["lx"]->doubleVal = (*particle)["x"]->doubleVal;
    (*particle)["ly"]->doubleVal = (*particle)["y"]->doubleVal;
    (*particle)["lz"]->doubleVal = (*particle)["z"]->doubleVal;
    // Add velocity vector
    (*particle)["x"]->doubleVal = (*particle)["x"]->doubleVal + (*particle)["vx"]->doubleVal * time_step.time_factor;
    (*particle)["y"]->doubleVal = (*particle)["y"]->doubleVal + (*particle)["vy"]->doubleVal * time_step.time_factor;
    (*particle)["z"]->doubleVal = (*particle)["z"]->doubleVal + (*particle)["vz"]->doubleVal * time_step.time_factor;

    // TODO: remove debug
    // logoutf("VelocityTransformation::Execute type: %d result: %2.2f += %2.2f * %2.2f", (*particle)["x"]->type, (*particle)["x"]->doubleVal, (*particle)["vx"]->doubleVal, time_step.time_factor);

}
