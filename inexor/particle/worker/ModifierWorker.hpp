/*
 * ModifierWorker.h
 *
 *  Created on: 01.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_WORKER_MODIFIERWORKER_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_WORKER_MODIFIERWORKER_H_

#include "inexor/entity/manager/EntityInstanceManager.hpp"
#include "inexor/entity/manager/RelationshipInstanceManager.hpp"
#include "inexor/particle/worker/ParticleWorker.hpp"
#include "inexor/util/Logging.hpp"

namespace inexor {
namespace entity {
namespace particle {

    /**
     * Specializes ParticleWorker for modifier instances.
     */
    class ModifierWorker : public ParticleWorker
    {
        public:
            ModifierWorker(std::string name, int maxfps, FunctionRefPtr function, InstanceRefPtr<EntityInstance> modifier_instance, std::shared_ptr<EntityInstanceManager> entity_instance_manager, std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager);
            virtual ~ModifierWorker();

            void Start();
            static int Work(void *data);

        private:
            /**
             * The particle modifier instance.
             */
            InstanceRefPtr<EntityInstance> modifier_instance;

            /**
             * The entity instance manager.
             */
            std::shared_ptr<EntityInstanceManager> entity_instance_manager;

            /**
             * The relationship instance manager.
             */
            std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager;

            /**
             * The relationship type:
             *
             *     modifier--[:modifies]-->particle
             */
            TypeRefPtr<RelationshipType> modifies;

    };

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_WORKER_MODIFIERWORKER_H_ */
