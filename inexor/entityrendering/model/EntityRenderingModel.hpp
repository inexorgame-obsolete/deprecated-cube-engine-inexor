/*
 * EntityModel.hpp
 *
 *  Created on: 15.02.2015
 *      Author: aschaeffer
 */

#ifndef INEXOR_ENTITY_RENDERING_MODEL_HEADER
#define INEXOR_ENTITY_RENDERING_MODEL_HEADER

#include <string>

namespace inexor {
namespace entity {

    // subsystems

    const std::string ENTITY_RENDERING_SUBSYSTEM("entity_rendering_subsystem");

    // entity attributes

    // const std::string POS("pos");

    // relationship type definitions

    const std::string REL_RENDERS_ENTITY("renders_entity");

    // entity type definitions

    const std::string ENT_ENTITY_RENDERER("entity_renderer");

    // Entity attribute names

    const std::string FUNC_RENDERS_ENTITY_ATTRIBUTE_NAME("renders_entity");

    // Entity function names

    const std::string ENT_FUNC_BOX_ENTITY_RENDERER("box_entity_renderer");

}
}

#endif /* INEXOR_ENTITY_RENDERING_MODEL_HEADER */
