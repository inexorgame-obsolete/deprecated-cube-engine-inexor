/*
 * DensityFadeout.cpp
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#include "DensityFadeout.h"

namespace inexor {
namespace entity {
namespace particle {

DensityFadeout::DensityFadeout() : EntityFunction(MODIFIER_DENSITY_FADEOUT_FUNCTION)
{
}

DensityFadeout::~DensityFadeout()
{
}

void DensityFadeout::Execute(TimeStep time_step, EntityInstance* modifier, EntityInstance* particle)
{
    float percent_done = (*particle)[ELAPSED]->intVal / ((*particle)[REMAINING]->intVal + (*particle)[ELAPSED]->intVal);
    if (percent_done > (*modifier)["density_threshold"]->floatVal)
    {
        (*particle)[DENSITY]->floatVal *= (1.0f - percent_done) * 10.0f * ((float) time_step.time_factor) * ((float) (*particle)["fadeout_frames"]->intVal);
    }
}

}
}
}
