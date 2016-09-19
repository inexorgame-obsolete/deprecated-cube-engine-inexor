#ifndef INEXOR_VSCRIPT_VSCRIPTSUBSYSTEM_HEADER
#define INEXOR_VSCRIPT_VSCRIPTSUBSYSTEM_HEADER

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/subsystem/SubsystemBase.hpp"
#include "inexor/vscript/provider/MemoryEntityTypeProvider.hpp"

#define VSCRIPT_SUBSYSTEM "vscript"

using namespace inexor::entity;

namespace inexor {
namespace vscript {

    /**
     * This subsystems manages teleporters.
     */
    class VScriptSubsystem : public SubsystemBase
    {
        public:

            VScriptSubsystem();
            VScriptSubsystem(
                CefRefPtr<EntityTypeManager> entity_type_manager,
                CefRefPtr<EntityInstanceManager> entity_instance_manager,
                CefRefPtr<RelationshipTypeManager> relationship_type_manager,
                CefRefPtr<RelationshipInstanceManager> relationship_instance_manager
            );
            virtual ~VScriptSubsystem();

            void Update(TimeStep time_step);
            void Cleanup();
            void Reset();

            InstanceRefPtr<EntityInstance> CreateMemory(double x, double y, double z);

            // InstanceRefPtr<RelationshipInstance> Connect(InstanceRefPtr<EntityInstance> teleport, InstanceRefPtr<EntityInstance> teledest);
            // void Disconnect(InstanceRefPtr<RelationshipInstance>);

            // void DeleteAll();
            // void DeleteAllTeleports();
            // void DeleteAllTeledests();
            // void DeleteAllConnections();

        private:

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(VScriptSubsystem);
    };

}
}

#endif /* INEXOR_VSCRIPT_VSCRIPTSUBSYSTEM_HEADER */
