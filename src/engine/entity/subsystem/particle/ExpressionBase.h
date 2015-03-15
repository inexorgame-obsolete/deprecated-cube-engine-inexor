/*
 * ExpressionBase.h
 *
 *  Created on: 08.03.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_EXPRESSIONBASE_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_EXPRESSIONBASE_H_

#include <cmath>
#include "muParser.h"

namespace inexor {
namespace entity {
namespace particle {

mu::value_type Ceil(mu::value_type v1);
mu::value_type Mod(mu::value_type v1, mu::value_type v2);
mu::value_type IntDiv(mu::value_type v1, mu::value_type v2);

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_EXPRESSIONBASE_H_ */
