#ifndef INEXOR_VSCRIPT_EVENT_TIMER_EVENT_HEADER
#define INEXOR_VSCRIPT_EVENT_TIMER_EVENT_HEADER

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityInstance.hpp"
#include "inexor/vscript/model/VScriptModel.hpp"
#include "inexor/util/Logging.hpp"

using namespace inexor::entity;

namespace inexor {
namespace vscript {

    class TimerEvent : public EntityFunction
    {
        public:

            TimerEvent();
            virtual ~TimerEvent();

            void Execute(TimeStep time_step, std::shared_ptr<EntityInstance> event_instance, std::shared_ptr<EntityInstance> target_entity_instance, std::shared_ptr<RelationshipInstance> activates_relationship_instance);

    };

}
}

#endif /* INEXOR_VSCRIPT_EVENT_TIMER_EVENT_HEADER */
