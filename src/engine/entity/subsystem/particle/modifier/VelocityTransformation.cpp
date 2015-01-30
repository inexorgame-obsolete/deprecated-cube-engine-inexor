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

void VelocityTransformation::Execute(TimeStep time_step, EntityInstance* particle)
{
	// Store last position
    // EntityInstance i = (*particle);
    (*particle)["lx"] = (*particle)["x"];
    (*particle)["ly"] = (*particle)["y"];
    (*particle)["lz"] = (*particle)["z"];
    // Add velocity vector
    (*particle)["x"]->doubleVal = (*particle)["x"]->doubleVal + (*particle)["vx"]->doubleVal * time_step.time_factor;
    (*particle)["y"]->doubleVal = (*particle)["y"]->doubleVal + (*particle)["vy"]->doubleVal * time_step.time_factor;
    (*particle)["z"]->doubleVal = (*particle)["z"]->doubleVal + (*particle)["vz"]->doubleVal * time_step.time_factor;

    logoutf("VelocityTransformation::Execute type: %d result: %2.2f += %2.2f * %2.2f", (*particle)["x"]->type, (*particle)["x"]->doubleVal, (*particle)["vx"]->doubleVal, time_step.time_factor);

}
