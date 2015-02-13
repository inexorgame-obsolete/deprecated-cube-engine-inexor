/*
 * SimpleGravity.cpp
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#include "SimpleGravity.h"

namespace inexor {
namespace entity {
namespace particle {

SimpleGravity::SimpleGravity()
    : EntityFunction(MODIFIER_SIMPLE_GRAVITY_FUNCTION),
      mass(200.0f),
      gravity(0.98f),
      dz(20.0f)
{
}

SimpleGravity::~SimpleGravity()
{
}

void SimpleGravity::Before(TimeStep time_step, EntityInstance* modifier)
{
    if ((*modifier).HasAttribute(MASS))
    {
        mass = (*modifier)[MASS]->floatVal;
    }
    if ((*modifier).HasAttribute(GRAVITY))
    {
        gravity = (*modifier)[GRAVITY]->floatVal;
    }
}

void SimpleGravity::Execute(TimeStep time_step, EntityInstance* modifier, EntityInstance* particle)
{
    float p_mass = (*particle)[MASS]->floatVal;
    (*particle)[VELOCITY]->vec3Val.z += ((-(p_mass) * mass * gravity / (dz * dz)) * dz) / (dz * p_mass);
}

}
}
}
