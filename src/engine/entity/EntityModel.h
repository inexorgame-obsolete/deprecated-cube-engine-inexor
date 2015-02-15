/*
 * EntityModel.h
 *
 *  Created on: 15.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_MODEL_H_
#define SRC_ENGINE_ENTITY_MODEL_H_

#include <string>

namespace inexor {
namespace entity {

    // Standard attributes

    const std::string POS("pos");

    // Relationship type definitions

    const std::string REL_ANY("*");
    const std::string REL_HANDLES("handles");
    const std::string REL_TELEPORTING("teleporting");

    // Entity type definitions

    const std::string ENT_ANY("*");
    const std::string ENT_HANDLE("handle");
    const std::string ENT_TELEPORT("teleport");
    const std::string ENT_TELEDEST("teledest");

    // Entity function definitions

    const std::string FUNC_TELEPORTED("teleported");

}
}

#endif /* SRC_ENGINE_ENTITY_MODEL_H_ */
