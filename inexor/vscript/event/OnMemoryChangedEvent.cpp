#include "OnMemoryChangedEvent.hpp"

namespace inexor {
namespace vscript {

    OnMemoryChangedEvent::OnMemoryChangedEvent() : EntityFunction(ENT_FUNC_TIMER_EVENT)
    {
    }

    OnMemoryChangedEvent::~OnMemoryChangedEvent()
    {
    }

    AttributeRefPtr OnMemoryChangedEvent::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> event_instance)
    {

        // always return true for now

    	spdlog::get("global")->info() << "OnMemoryChangedEvent::Execute";
    	AttributeRefPtr return_value = std::make_shared<EntityAttribute>(true);
    	return return_value;

    	// TODO: get incoming relationships of type memory_input
    }

}
}
