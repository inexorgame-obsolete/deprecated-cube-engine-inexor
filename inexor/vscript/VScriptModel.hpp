#ifndef INEXOR_VSCRIPT_VSCRIPTMODEL_HEADER
#define INEXOR_VSCRIPT_VSCRIPTMODEL_HEADER

#include <string>

#include "inexor/entity/EntityModel.hpp"

namespace inexor {
namespace vscript {

    // subsystems

    // const std::string SYS_HANDLE("handle_subsystem");

    // entity attributes

    // const std::string POS("pos");

    // relationship type definitions

    // const std::string REL_TELEPORTING("teleporting");

    // entity type definitions

    const std::string ENT_MEMORY("memory");
    const std::string ENT_BOOL_MEMORY("bool_memory");

    // entity function definitions

    // const std::string FUNC_TELEPORTED("teleported");

    // attribute names

    // const std::string FUNC_RENDERS_HANDLE_ATTRIBUTE_NAME("renders_handle");


    // Type factories

    const std::string BOOL_MEMORY_TYPE_FACTORY("bool_memory_type_factory");

    // Type prefixes

    const std::string ENTTYPE_PREFIX_BOOL_MEMORY_TYPE("bool_memory_type_");

    // Function attribute names

    const std::string BOOL_MEMORY_FUNCTION_ATTRIBUTE_NAME("todo");

}
}

#endif /* INEXOR_VSCRIPT_VSCRIPTMODEL_HEADER */
