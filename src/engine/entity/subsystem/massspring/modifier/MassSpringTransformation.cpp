/*
 * MassSpringTransformation.cpp
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#include "MassSpringTransformation.h"

namespace inexor {
namespace entity {
namespace massspring {

MassSpringTransformation::MassSpringTransformation() : EntityFunction(FUNC_MASSSPRING_TRANSFORMATION)
{
}

MassSpringTransformation::~MassSpringTransformation()
{
}

void MassSpringTransformation::Execute(TimeStep time_step, RelationshipInstance* spring)
{
}

}
}
}
