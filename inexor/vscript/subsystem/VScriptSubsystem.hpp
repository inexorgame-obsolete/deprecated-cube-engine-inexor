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
                std::shared_ptr<EntityTypeManager> entity_type_manager,
                std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager
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

    };

}
}

#endif /* INEXOR_VSCRIPT_VSCRIPTSUBSYSTEM_HEADER */
