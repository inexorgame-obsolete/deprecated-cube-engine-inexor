#ifndef INEXOR_VSCRIPT_EVENT_ON_MEMORY_CHANGED_EVENT_HEADER
#define INEXOR_VSCRIPT_EVENT_ON_MEMORY_CHANGED_EVENT_HEADER

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityInstance.hpp"
#include "inexor/vscript/model/VScriptModel.hpp"
#include "inexor/util/Logging.hpp"

using namespace inexor::entity;

namespace inexor {
namespace vscript {

    class OnMemoryChangedEvent : public EntityFunction
    {
        public:

            OnMemoryChangedEvent();
            virtual ~OnMemoryChangedEvent();

            /**
             * Returns true, if the memory has changed.
             */
            AttributeRefPtr Execute(TimeStep time_step, std::shared_ptr<EntityInstance> event_instance);

    };

}
}

#endif /* INEXOR_VSCRIPT_EVENT_ON_MEMORY_CHANGED_EVENT_HEADER */
