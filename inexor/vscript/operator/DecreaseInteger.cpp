#include "../operator/DecreaseInteger.hpp"

namespace inexor {
namespace vscript {

    DecreaseInteger::DecreaseInteger() : EntityFunction(ENT_FUNC_DECREASE_INTEGER)
    {
    }

    DecreaseInteger::~DecreaseInteger()
    {
    }

    void DecreaseInteger::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> activator_instance, std::shared_ptr<EntityInstance> integer_memory_instance, std::shared_ptr<RelationshipInstance> activates)
    {
    	int value = integer_memory_instance->GetAttribute("value")->intVal--;
    }

}
}
