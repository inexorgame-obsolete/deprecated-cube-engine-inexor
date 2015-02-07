/*
 * MathFunction.cpp
 *
 *  Created on: 30.01.2015
 *      Author: aschaeffer
 */

#include "MathFunction.h"

namespace inexor {
namespace entity {

MathFunction::MathFunction(std::string name, std::string expression) : EntityFunction(name), expression(expression)
{
}

MathFunction::~MathFunction()
{
}

std::string MathFunction::GetExpression()
{
    return expression;
}

void MathFunction::SetExpression(std::string expression)
{
    this->expression = expression;
}

}
}
