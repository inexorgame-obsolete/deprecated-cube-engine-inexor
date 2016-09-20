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
                std::shared_ptr<EntityTypeManager> entity_type_manager,
                std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager
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

    };

}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_TELEPORTSUBSYSTEM_H_ */
