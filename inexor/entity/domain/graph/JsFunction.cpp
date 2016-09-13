/*
 * JsFunction.cpp
 *
 *  Created on: 30.01.2015
 *      Author: aschaeffer
 */

#include "JsFunction.h"

namespace inexor {
namespace entity {

JsFunction::JsFunction(std::string name, std::string callback_name) : EntityFunction(name), callback_name(callback_name)
{
}

JsFunction::~JsFunction()
{
}

std::string JsFunction::GetCallbackName()
{
    return callback_name;
}

void JsFunction::SetCallbackName(std::string callback_name)
{
    this->callback_name = callback_name;
}

}
}
