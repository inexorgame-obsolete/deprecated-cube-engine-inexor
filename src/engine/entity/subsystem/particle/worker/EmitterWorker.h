/*
 * EmitterWorker.h
 *
 *  Created on: 01.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_WORKER_EMITTERWORKER_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_WORKER_EMITTERWORKER_H_

#include "ParticleWorker.h"

/**
 * Specializes ParticleWorker for emitter instances.
 */
class EmitterWorker : public ParticleWorker
{
    public:
        EmitterWorker(std::string name, FunctionRefPtr function, InstanceRefPtr<EntityInstance> emitter_instance);
        virtual ~EmitterWorker();

        void Start();
        static int Work(void *data);

    private:
        /**
         * The particle emitter instance.
         */
        InstanceRefPtr<EntityInstance> emitter_instance;

        /**
         * The emitted particles are of this type.
         * TODO: track changes on the emitter_instance to this reference!
         */
        TypeRefPtr<EntityType> particle_type;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EmitterWorker);
};

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_WORKER_EMITTERWORKER_H_ */
