#ifndef INEXOR_VSCRIPT_VSCRIPT_TEST_HEADER
#define INEXOR_VSCRIPT_VSCRIPT_TEST_HEADER

#include "inexor/entity/EntitySystem.hpp"
#include "inexor/vscript/subsystem/VScriptSubsystem.hpp"
#include "inexor/util/Logging.hpp"

using namespace inexor::entity;

namespace inexor {
namespace vscript {

    class VScriptTest
    {
        public:

            VScriptTest(std::shared_ptr<EntitySystem> entity_system);
            virtual ~VScriptTest();

            void RunTests();
            void SubsystemTest();

        private:
            std::shared_ptr<EntitySystem> entity_system;

            TypeRefPtr<EntityType> timer_event_type;
            TypeRefPtr<EntityType> integer_memory_type;

    };

}
}

#endif /* INEXOR_VSCRIPT_VSCRIPT_TEST_HEADER */
