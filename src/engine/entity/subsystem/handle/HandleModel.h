/*
 * HandleModel.h
 *
 *  Created on: 21.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_SUBSYSTEM_HANDLE_MODEL_H_
#define SRC_ENGINE_SUBSYSTEM_HANDLE_MODEL_H_

#include <string>

namespace inexor {
namespace entity {
namespace handle {

    // Handle attributes

    const std::string SELECTED("selected");
    const std::string HOVERED("hovered");
    const std::string DIST("dist");

    // Relationship type definitions

    const std::string REL_HANDLES("handles");
    const std::string REL_RENDERS_HANDLE("renders_handle");

    // Entity type definitions

    const std::string ENT_HANDLE("handle");
    const std::string ENT_HANDLE_RENDERER("handle_renderer");

    // Entity function definitions

    const std::string FUNC_RENDERS_HANDLE("renders_handle");
    const std::string FUNC_BOX_HANDLE_RENDERER("box_handle_renderer");

    // Attribute names

    const std::string FUNC_RENDERS_HANDLE_ATTRIBUTE_NAME("renders_handle");

}
}
}

#endif /* SRC_ENGINE_SUBSYSTEM_HANDLE_MODEL_H_ */
