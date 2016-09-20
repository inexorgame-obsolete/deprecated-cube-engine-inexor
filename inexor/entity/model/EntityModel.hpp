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

    // subsystems

    const std::string SYS_HANDLE("handle_subsystem");
    const std::string SYS_TELEPORT("teleport_subsystem");

    // entity attributes

    const std::string POS("pos");
    const std::string TYPE("type");
    const std::string DIR("direction");
    const std::string DIM("dimension");

    // relationship type definitions

    const std::string REL_ANY("*");
    const std::string REL_HANDLES("handles");
    const std::string REL_RENDERS_HANDLE("renders_handle");
    const std::string REL_TELEPORTING("teleporting");

    // entity type definitions

    const std::string ENT_ANY("*");
    const std::string ENT_HANDLE("handle");
    const std::string ENT_HANDLE_RENDERER("handle_renderer");
    const std::string ENT_TELEPORT("teleport");
    const std::string ENT_TELEDEST("teledest");

    // entity function definitions

    const std::string FUNC_TELEPORTED("teleported");
    const std::string FUNC_RENDERS_HANDLE("renders_handle");
    const std::string FUNC_BOX_HANDLE_RENDERER("box_handle_renderer");

    // attribute names

    const std::string FUNC_RENDERS_HANDLE_ATTRIBUTE_NAME("renders_handle");

}
}

#endif /* SRC_ENGINE_ENTITY_MODEL_H_ */
