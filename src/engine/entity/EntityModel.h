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

    // Subsystems

    const std::string SYS_HANDLE("handle_subsystem");
    const std::string SYS_TELEPORT("teleport_subsystem");

    // Entity attributes

    const std::string POS("pos");
    const std::string TYPE("type");
    const std::string DIR("direction");
    const std::string DIM("dimension");

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

    // Handle types

    const int HANDLE_POINT = 1;

}
}

#endif /* SRC_ENGINE_ENTITY_MODEL_H_ */
