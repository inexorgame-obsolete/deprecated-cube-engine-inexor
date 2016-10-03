#include "PrintAction.hpp"

namespace inexor {
namespace vscript {

    PrintAction::PrintAction() : EntityFunction(ENT_FUNC_ACTION_PRINT)
    {
    }

    PrintAction::~PrintAction()
    {
    }

    AttributeRefPtr PrintAction::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> event_instance, std::shared_ptr<EntityInstance> entity_instance, std::shared_ptr<RelationshipInstance> activates_relationship_instance)
    {
        AttributeRefPtr attribute = activates_relationship_instance.get()->GetAttribute("value");
        switch (attribute->type) {
            case ENTATTR_INT:
                spdlog::get("global")->info() << "" << attribute->intVal;
                break;
            case ENTATTR_FLOAT:
                spdlog::get("global")->info() << "" << attribute->floatVal;
                break;
            case ENTATTR_DOUBLE:
                spdlog::get("global")->info() << "" << attribute->doubleVal;
                break;
            case ENTATTR_FALSE:
            case ENTATTR_TRUE:
                spdlog::get("global")->info() << "" << attribute->GetBool();
                break;
            case ENTATTR_STRING:
                spdlog::get("global")->info() << "" << attribute->stringVal;
                break;
            case ENTATTR_NULL:
                spdlog::get("global")->info() << "null";
                break;
            case ENTATTR_FUNCTION:
                spdlog::get("global")->info() << "function";
                // TODO: print out which function
                break;
            default:
                return false;
        }
        return true;
    }

}
}
