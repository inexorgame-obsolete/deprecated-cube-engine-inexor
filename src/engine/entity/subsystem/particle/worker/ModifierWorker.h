/*
 * ModifierWorker.h
 *
 *  Created on: 01.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_WORKER_MODIFIERWORKER_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_WORKER_MODIFIERWORKER_H_

#include "ParticleWorker.h"

/**
 * Specializes ParticleWorker for modifier instances.
 */
class ModifierWorker : public ParticleWorker
{
    public:
        ModifierWorker(std::string name, FunctionRefPtr function, InstanceRefPtr<EntityInstance> modifier_instance);
        virtual ~ModifierWorker();

        void Start();
        static int Work(void *data);

    private:
        /**
         * The particle modifier instance.
         */
        InstanceRefPtr<EntityInstance> modifier_instance;

        /**
         * The relationship type:
         *
         *     modifier--[:modifies]-->particle
         */
        TypeRefPtr<RelationshipType> modifies;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(ModifierWorker);
};

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_WORKER_MODIFIERWORKER_H_ */
