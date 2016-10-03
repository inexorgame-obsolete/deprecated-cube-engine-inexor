#ifndef INEXOR_VSCRIPT_VSCRIPTSUBSYSTEM_HEADER
#define INEXOR_VSCRIPT_VSCRIPTSUBSYSTEM_HEADER

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/subsystem/SubsystemBase.hpp"
#include "inexor/vscript/action/PrintAction.hpp"
#include "inexor/vscript/manager/ActionManager.hpp"
#include "inexor/vscript/manager/AreaManager.hpp"
#include "inexor/vscript/manager/EventManager.hpp"
#include "inexor/vscript/manager/MemoryManager.hpp"
#include "inexor/vscript/manager/OperatorManager.hpp"

using namespace inexor::entity;

namespace inexor {
namespace vscript {

    /**
     * This subsystems manages 3D visual scripting.
     */
    class VScriptSubsystem : public SubsystemBase
    {
        public:

            VScriptSubsystem();
            
            /**
             *
             */
            VScriptSubsystem(std::shared_ptr<EntityTypeManager> entity_type_manager,
                             std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                             std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                             std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager);
            virtual ~VScriptSubsystem();

            /**
             * Updates all activations. Start point are all event entities.
             */
            void Update(TimeStep time_step);

            /**
             * Cleanup the visual scripting subsystem.
             */
            void Cleanup();

            /**
             * Resets the visual scripting subsystem.
             */
            void Reset();

            /**
             * Returns the action manager which is responsible for
             * managing the action nodes.
             */
            std::shared_ptr<ActionManager> GetActionManager();

            /**
             * Returns the area manager which is responsible for
             * managing the area nodes.
             */
            std::shared_ptr<AreaManager> GetAreaManager();

            /**
             * Returns the event manager which is responsible for
             * managing the event nodes.
             */
            std::shared_ptr<EventManager> GetEventManager();

            /**
             * Returns the memory manager which is responsible for
             * managing the memory nodes.
             */
            std::shared_ptr<MemoryManager> GetMemoryManager();

            /**
             * Returns the operator manager which is responsible for
             * managing the operator nodes.
             */
            std::shared_ptr<OperatorManager> GetOperatorManager();

        private:

            /**
             * The action manager.
             */
            std::shared_ptr<ActionManager> action_manager;

            /**
             * The area manager.
             */
            std::shared_ptr<AreaManager> area_manager;

            /**
             * The event manager.
             */
            std::shared_ptr<EventManager> event_manager;

            /**
             * The memory manager.
             */
            std::shared_ptr<MemoryManager> memory_manager;

            /**
             * The operator manager.
             */
            std::shared_ptr<OperatorManager> operator_manager;

    };

}
}

/**
 * Provide the vscript subsystem as global reference.
 */
extern std::shared_ptr<inexor::vscript::VScriptSubsystem> vscript_subsystem;

#endif /* INEXOR_VSCRIPT_VSCRIPTSUBSYSTEM_HEADER */
