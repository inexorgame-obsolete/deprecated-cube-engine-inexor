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

void VelocityTransformation::Execute(EntityInstance* particle, float time_factor)
{
	// Store last position
    particle["lx"] = particle["x"];
    particle["ly"] = particle["y"];
    particle["lz"] = particle["z"];
    // Add velocity vector
    particle["x"] += particle["vx"] * time_factor;
    particle["y"] += particle["vy"] * time_factor;
    particle["z"] += particle["vz"] * time_factor;
}
