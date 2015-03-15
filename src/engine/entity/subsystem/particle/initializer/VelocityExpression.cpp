/*
 * VelocityExpression.cpp
 *
 *  Created on: 09.03.2015
 *      Author: aschaeffer
 */

#include "VelocityExpression.h"

namespace inexor {
namespace entity {
namespace particle {

VelocityExpression::VelocityExpression(std::string expression)
    : EntityFunction(INITIALIZER_VELOCITY_EXPRESSION_FUNCTION), args(8), expression(expression)
{
    parser.DefineVar("time", &time);
    parser.DefineVar("sn", &sequence_number);
    parser.DefineVar("ex", &emitter_x);
    parser.DefineVar("ey", &emitter_y);
    parser.DefineVar("ez", &emitter_z);
    parser.DefineVar("px", &particle_x);
    parser.DefineVar("py", &particle_y);
    parser.DefineVar("pz", &particle_z);

    parser.DefineOprt(_T("%"), particle::Mod, true);
    parser.DefineOprt(_T("div"), particle::IntDiv, true);
    parser.DefineFun(_T("ceil"), particle::Ceil);

	parser.SetExpr(expression);
}

VelocityExpression::~VelocityExpression()
{
}

void VelocityExpression::SetExpression(std::string expression)
{
    if (this->expression != expression)
    {
        this->expression = expression;
        parser.SetExpr(expression);
    }
}

void VelocityExpression::Execute(TimeStep time_step, EntityInstance* emitter, EntityInstance* initializer, EntityInstance* particle)
{
    SetExpression(initializer->GetType()[EXPRESSION]->stringVal);
    time = (float) SDL_GetTicks();
    sequence_number = (*particle)[SEQUENCE_NUMBER]->intVal;
    vec e((*emitter)[POS]->vec3Val);
    vec p((*particle)[POS]->vec3Val);
    emitter_x = e.x;
    emitter_y = e.y;
    emitter_z = e.z;
    particle_x = p.x;
    particle_y = p.y;
    particle_z = p.z;
    try {
        mu::value_type *v = parser.Eval(args);
        (*particle)[VELOCITY]->vec3Val = vec(v[0], v[1], v[2]);
    } catch (mu::Parser::exception_type &e) {
        logoutf("Error parsing position expression %s: %s", e.GetExpr().c_str(), e.GetMsg().c_str());
    }
}

}
}
}
