/*
 * PulseInitializer.cpp
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#include "TimerEvent.hpp"

namespace inexor {
namespace vscript {

    TimerEvent::TimerEvent() : EntityFunction(ENT_FUNC_TIMER_EVENT)
    {
    }

    TimerEvent::~TimerEvent()
    {
    }

    void TimerEvent::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> event_instance, std::shared_ptr<EntityInstance> entity_instance, std::shared_ptr<RelationshipInstance> activates_relationship_instance)
    {
        // (*event_instance)
    	// (*entity_instance)
    	// time_step.time_factor
    	spdlog::get("global")->info() << "TimerEvent::Execute";
    }

}
}
