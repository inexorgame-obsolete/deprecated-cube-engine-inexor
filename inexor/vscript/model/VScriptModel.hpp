#ifndef INEXOR_VSCRIPT_VSCRIPTMODEL_HEADER
#define INEXOR_VSCRIPT_VSCRIPTMODEL_HEADER

#include <string>

#include "inexor/entity/model/EntityModel.hpp"

namespace inexor {
namespace vscript {

    // Subsystems

    // const std::string SUBSYSTEM_VSCRIPTSYS_HANDLE("vscript_subsystem");

    // Entity attributes

    // const std::string POS("pos");

    // Relationship type definitions

    const std::string REL_ACTIVATES("activates");

    // Entity type definitions

    const std::string ENT_MEMORY("memory");
    const std::string ENT_BOOL_MEMORY("bool_memory");
    const std::string ENT_INTEGER_MEMORY("integer_memory");
    const std::string ENT_FLOAT_MEMORY("float_memory");

    const std::string ENT_EVENT("event");
    const std::string ENT_TIMER_EVENT("timer_event");
    const std::string ENT_PLAYER_COLLIDE_EVENT("player_collide_event");

    // Entity function definitions

    // const std::string FUNC_TELEPORTED("teleported");

    // Attribute names

    // const std::string FUNC_RENDERS_HANDLE_ATTRIBUTE_NAME("renders_handle");

    // Type factories

    const std::string BOOL_MEMORY_TYPE_FACTORY("bool_memory_type_factory");
    const std::string INTEGER_MEMORY_TYPE_FACTORY("integer_memory_type_factory");

    // Type prefixes

    const std::string ENTTYPE_PREFIX_BOOL_MEMORY_TYPE("bool_memory_type_");
    const std::string ENTTYPE_PREFIX_INTEGER_MEMORY_TYPE("integer_memory_type_");
    const std::string ENTTYPE_PREFIX_FLOAT_MEMORY_TYPE("integer_memory_type_");

    // Function attribute names

    const std::string BOOL_MEMORY_FUNCTION_ATTRIBUTE_NAME("todo");
    const std::string INTEGER_MEMORY_FUNCTION_ATTRIBUTE_NAME("todo2");

    const std::string ENT_ATTR_ACTIVATION_FUNCTION("activation_function");

    // Function names

    const std::string ENT_FUNC_ACTIVATION("activation");
    const std::string ENT_FUNC_TIMER_EVENT("timer_event");
    const std::string ENT_FUNC_INCREASE_INTEGER("increase");
    const std::string ENT_FUNC_DECREASE_INTEGER("decrease");

}
}

#endif /* INEXOR_VSCRIPT_VSCRIPTMODEL_HEADER */
