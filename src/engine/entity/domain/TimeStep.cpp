/*
 * TimeStep.cpp
 *
 *  Created on: 30.01.2015
 *      Author: aschaeffer
 */

#include "TimeStep.h"

TimeStep::TimeStep(int elapsed_time, double time_factor, double time_unit)
    : elapsed_time(elapsed_time), time_factor(time_factor), time_unit(time_unit)
{
}

TimeStep::~TimeStep()
{
}

