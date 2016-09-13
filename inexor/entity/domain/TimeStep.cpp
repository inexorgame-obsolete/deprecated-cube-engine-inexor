/*
 * TimeStep.cpp
 *
 *  Created on: 30.01.2015
 *      Author: aschaeffer
 */

#include "TimeStep.h"

namespace inexor {
namespace entity {

TimeStep::TimeStep(int elapsed_millis, double time_factor, double time_unit)
    : elapsed_millis(elapsed_millis), time_factor(time_factor), time_unit(time_unit)
{
}

TimeStep::TimeStep(int elapsed_millis, double time_unit)
    : elapsed_millis(elapsed_millis), time_unit(time_unit)
{
    time_factor = (double) elapsed_millis / time_unit;
}

TimeStep::~TimeStep()
{
}

}
}
