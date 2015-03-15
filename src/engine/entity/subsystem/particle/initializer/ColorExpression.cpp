/*
 * ColorExpression.cpp
 *
 *  Created on: 08.03.2015
 *      Author: aschaeffer
 */

#include "ColorExpression.h"

namespace inexor {
namespace entity {
namespace particle {

ColorExpression::ColorExpression(std::string expression)
    : EntityFunction(INITIALIZER_COLOR_EXPRESSION_FUNCTION), args(8), expression(expression)
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

ColorExpression::~ColorExpression()
{
}

void ColorExpression::SetExpression(std::string expression)
{
    if (this->expression != expression)
    {
        this->expression = expression;
        parser.SetExpr(expression);
    }
}

void ColorExpression::Execute(TimeStep time_step, EntityInstance* emitter, EntityInstance* initializer, EntityInstance* particle)
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
        (*particle)[COLOR]->vec4Val = vec4(v[0], v[1], v[2], v[3]);
    } catch (mu::Parser::exception_type &e) {
        logoutf("Error parsing color expression %s: %s", e.GetExpr().c_str(), e.GetMsg().c_str());
    }
}

}
}
}
