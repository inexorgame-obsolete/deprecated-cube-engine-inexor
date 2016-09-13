/*
 * GravityPoint.cpp
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#include "GravityPoint.hpp"

namespace inexor {
namespace entity {
namespace particle {

GravityPoint::GravityPoint() : EntityFunction(MODIFIER_GRAVITY_POINT_FUNCTION)
{
}

GravityPoint::~GravityPoint()
{
}

void GravityPoint::Execute(TimeStep time_step, EntityInstance* modifier, EntityInstance* particle)
{
    float m_gravity = (*modifier)[GRAVITY]->floatVal;
    float m_mass = (*modifier)[MASS]->floatVal;
    float p_mass = (*particle)[MASS]->floatVal;
    vec d((*particle)[POS]->vec3Val);
    d.sub((*modifier)[POS]->vec3Val);
    float distance = d.magnitude();
    if (distance == 0.0f)
        distance = 0.00000000001f;
    float force = (-p_mass) * m_mass * m_gravity * ((float) time_step.time_factor) / (distance * distance);
    // logoutf(">>>>>>>>>>>>>>>> force: %2.2f distance: %2.2f p_mass: %2.2f m_mass: %2.2f m_gravity: %2.2f", force, distance, p_mass, m_mass, m_gravity);
    d.mul(force).div(distance * p_mass);
    (*particle)[VELOCITY]->vec3Val.add(d);
}

}
}
}
