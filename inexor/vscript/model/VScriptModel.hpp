#ifndef INEXOR_VSCRIPT_VSCRIPTMODEL_HEADER
#define INEXOR_VSCRIPT_VSCRIPTMODEL_HEADER

#include <string>

#include "inexor/entity/model/EntityModel.hpp"

namespace inexor {
namespace vscript {

    // Subsystem definitions

    const std::string SUBSYSTEM_VSCRIPT("vscript_subsystem");

    // Entity type definitions

    const std::string ENT_TYPE_ACTION("action");
    const std::string ENT_TYPE_AREA("area");
    const std::string ENT_TYPE_EVENT("event");
    const std::string ENT_TYPE_MEMORY("memory");
    const std::string ENT_TYPE_OPERATOR("operator");

    // Event functions

    const std::string ENT_FUNC_EVENT_CHECK("event_check");
    // const std::string ENT_FUNC_EVENT_CHECK("event_check");

    // Event entity types

    const std::string ENT_TYPE_EVENT_ON_MEMORY_CHANGED("on_memory_changed");
    const std::string ENT_TYPE_EVENT_ON_TIMER("on_timer");

    // Relationship type definitions

    const std::string REL_TYPE_EXECUTES("executes");











    const std::string ENT_TYPE_EVENT_PLAYER_COLLIDE("player_collide_event");

    const std::string ENT_TYPE_MEMORY_BOOL("bool_memory");
    const std::string ENT_TYPE_MEMORY_INTEGER("integer_memory");
    const std::string ENT_TYPE_MEMORY_FLOAT("float_memory");
    const std::string ENT_TYPE_MEMORY_STRING("string_memory");

    const std::string ENT_TYPE_OPERATOR_ADD("add_operator");
    const std::string ENT_TYPE_OPERATOR_SUB("sub_operator");

    const std::string ENT_TYPE_ACTION_PRINT("print_action");

    const std::string ENT_TYPE_ATTR_PROPAGATE("propagate");
    const std::string ENT_TYPE_ATTR_GET("get");
    const std::string ENT_TYPE_ATTR_SET("set");








    // Relationship type definitions

    const std::string REL_ACTIVATES("activates");

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
    const std::string ENT_FUNC_ACTION_PRINT("print");

    const std::string ENT_FUNC_ACTIVATION("activation");
    const std::string ENT_FUNC_TIMER_EVENT("timer_event");
    const std::string ENT_FUNC_INCREASE_INTEGER("increase");
    const std::string ENT_FUNC_DECREASE_INTEGER("decrease");

}
}

#endif /* INEXOR_VSCRIPT_VSCRIPTMODEL_HEADER */
