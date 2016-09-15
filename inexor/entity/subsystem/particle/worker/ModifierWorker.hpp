/*
 * ModifierWorker.h
 *
 *  Created on: 01.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_WORKER_MODIFIERWORKER_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_WORKER_MODIFIERWORKER_H_

#include "ParticleWorker.hpp"
#include "../../../manager/EntityInstanceManager.hpp"
#include "../../../manager/RelationshipInstanceManager.hpp"

namespace inexor {
namespace entity {
namespace particle {

    /**
     * Specializes ParticleWorker for modifier instances.
     */
    class ModifierWorker : public ParticleWorker
    {
        public:
            ModifierWorker(std::string name, int maxfps, FunctionRefPtr function, InstanceRefPtr<EntityInstance> modifier_instance, CefRefPtr<EntityInstanceManager> entity_instance_manager, CefRefPtr<RelationshipInstanceManager> relationship_instance_manager);
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
            CefRefPtr<EntityInstanceManager> entity_instance_manager;

            /**
             * The relationship instance manager.
             */
            CefRefPtr<RelationshipInstanceManager> relationship_instance_manager;

            /**
             * The relationship type:
             *
             *     modifier--[:modifies]-->particle
             */
            TypeRefPtr<RelationshipType> modifies;

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(ModifierWorker);
    };

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_WORKER_MODIFIERWORKER_H_ */
