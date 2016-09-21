/*
 * Rolling.cpp
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#include "Rolling.hpp"

namespace inexor {
namespace entity {
namespace particle {

    Rolling::Rolling() : EntityFunction(MODIFIER_ROLLING_FUNCTION)
    {
    }

    Rolling::~Rolling()
    {
    }

    void Rolling::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> modifier, std::shared_ptr<EntityInstance> particle)
    {
        vec l((*particle)[LAST_POS]->vec3Val);
        (*particle)[ROLL]->floatVal += l.sub((*particle)[POS]->vec3Val).magnitude() / (4 * RAD);
    }

}
}
}
