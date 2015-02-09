/*
 * Rolling.cpp
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#include "Rolling.h"

namespace inexor {
namespace entity {
namespace particle {

Rolling::Rolling() : EntityFunction(MODIFIER_ROLLING_FUNCTION)
{
}

Rolling::~Rolling()
{
}

void Rolling::Execute(TimeStep time_step, EntityInstance* modifier, EntityInstance* particle)
{
    (*particle)[ROLL]->doubleVal += (*particle)[LAST_POS]->vec3Val.magnitude() / (4 * RAD);
}

}
}
}
