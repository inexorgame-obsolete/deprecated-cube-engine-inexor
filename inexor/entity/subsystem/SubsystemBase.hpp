/*
 * SubsystemBase.hpp
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_SUBSYSTEMBASE_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_SUBSYSTEMBASE_H_

#include "../EntitySystemBase.hpp"
#include "../domain/TimeStep.hpp"
#include "../manager/EntityTypeManager.hpp"
#include "../manager/EntityInstanceManager.hpp"
#include "../manager/RelationshipTypeManager.hpp"
#include "../manager/RelationshipInstanceManager.hpp"
#include "inexor/util/Logging.hpp"

namespace inexor {
namespace entity {

    /**
     * Base class for subsystem managers.
     */
    class SubsystemBase
    {
        public:

            SubsystemBase(std::string name);
            SubsystemBase(
                std::string name,
                std::shared_ptr<EntityTypeManager> entity_type_manager,
                std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager
            );
            virtual ~SubsystemBase() {}

            /**
             *
             */
            virtual void Update(TimeStep time_step);

            /**
             *
             */
            virtual void Cleanup();

            /**
             *
             */
            virtual void Reset();

            /**
             * Get the name of this subsystem
             */
            std::string GetName();

            /**
             * Set the name of this subsystem
             */
            void SetName(std::string);

            /**
             *
             */
            void SetEntityTypeManager(std::shared_ptr<EntityTypeManager> entity_type_manager);

            /**
             *
             */
            void SetEntityInstanceManager(std::shared_ptr<EntityInstanceManager> entity_instance_manager);

            /**
             *
             */
            void SetRelationshipTypeManager(std::shared_ptr<RelationshipTypeManager> relationship_type_manager);

            /**
             *
             */
            void SetRelationshipInstanceManager(std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager);

        protected:

            std::string name;

            std::shared_ptr<EntityTypeManager> entity_type_manager;
            std::shared_ptr<EntityInstanceManager> entity_instance_manager;

            std::shared_ptr<RelationshipTypeManager> relationship_type_manager;
            std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager;

    };

}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_SUBSYSTEMBASE_H_ */
