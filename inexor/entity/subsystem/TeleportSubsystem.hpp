/*
 * TeleportSubsystem.h
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_TELEPORTSUBSYSTEM_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_TELEPORTSUBSYSTEM_H_

#include "../EntitySystemBase.hpp"
#include "../provider/TeleportEntityTypeProvider.hpp"
#include "SubsystemBase.hpp"

#define TELEPORT_SUBSYSTEM "teleport"

namespace inexor {
namespace entity {

    /**
     * This subsystems manages teleporters.
     */
    class TeleportSubsystem : public SubsystemBase
    {
        public:

            TeleportSubsystem();
            TeleportSubsystem(
                CefRefPtr<EntityTypeManager> entity_type_manager,
                CefRefPtr<EntityInstanceManager> entity_instance_manager,
                CefRefPtr<RelationshipTypeManager> relationship_type_manager,
                CefRefPtr<RelationshipInstanceManager> relationship_instance_manager
            );
            virtual ~TeleportSubsystem();

            void Update(TimeStep time_step);
            void Cleanup();
            void Reset();

            InstanceRefPtr<EntityInstance> CreateTeleport(double x, double y, double z);
            InstanceRefPtr<EntityInstance> CreateTeledest(double x, double y, double z);

            InstanceRefPtr<RelationshipInstance> Connect(InstanceRefPtr<EntityInstance> teleport, InstanceRefPtr<EntityInstance> teledest);
            void Disconnect(InstanceRefPtr<RelationshipInstance>);

            void DeleteAll();
            void DeleteAllTeleports();
            void DeleteAllTeledests();
            void DeleteAllConnections();

        private:

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(TeleportSubsystem);
    };

}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_TELEPORTSUBSYSTEM_H_ */
