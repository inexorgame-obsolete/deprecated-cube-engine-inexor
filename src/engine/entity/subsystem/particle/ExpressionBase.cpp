/*
 * ExpressionBase.cpp
 *
 *  Created on: 08.03.2015
 *      Author: aschaeffer
 */

#include "ExpressionBase.h"

namespace inexor {
namespace entity {
namespace particle {

/*
static int Round(mu::value_type v)
{
    return (int)(v + ((v>=0) ? 0.5 : -0.5) );
}
*/

mu::value_type Ceil(mu::value_type v1)
{
    return std::ceil(v1);
}

mu::value_type Mod(mu::value_type v1, mu::value_type v2)
{
    return std::fmod(v1, v2);
}

mu::value_type IntDiv(mu::value_type v1, mu::value_type v2)
{
    return std::ceil(v1 / v2);
}


}
}
}
