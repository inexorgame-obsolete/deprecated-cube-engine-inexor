/*
 * ParticleWorker.h
 *
 *  Created on: 31.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_PARTICLEWORKER_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_PARTICLEWORKER_H_

#include "inexor/engine/engine.hpp"
#include "../../../EntitySystemBase.h"
#include "../../../domain/TimeStep.h"
#include "../../../domain/InstanceRefPtr.h"
#include "../../../domain/FunctionRefPtr.h"
#include "../../../domain/graph/EntityInstance.h"

namespace inexor {
namespace entity {
namespace particle {

/**
 * Worker thread container for calculate particle physics in it's own thread.
 */
class ParticleWorker
{
    public:
        ParticleWorker();
        ParticleWorker(std::string name, int maxfps, FunctionRefPtr function);
        virtual ~ParticleWorker();

        /**
         * Starts the thread. Overwrite this in custom workers.
         */
        virtual void Start();

        /**
         * Stops the thread.
         */
        virtual void Stop();

        /**
         * The worker implementation. Must be static. Overwrite this in custom
         * workers.
         */
        static int Work(void *data);

        /**
         * Returns the name of the worker.
         */
        std::string GetName();

        /**
         * Sets the worker function.
         */
        void SetFunction(FunctionRefPtr function);

        /**
         * Reset the timer. Elapsed millis, frame millis, frame last millis and
         * time unit are set to defaults.
         */
        void ResetTimer();

        /**
         * Sets the time unit.
         */
        void SetTimeUnit(double time_unit);

        /**
         * Limits the frames per second.
         */
        void LimitFps(int &millis, int curmillis, int maxfps);

    protected:

        /**
        * The worker thread.
        */
        SDL_Thread *thread;

        /**
         * The name of the worker.
         */
        std::string name;

        /**
        * If true, the worker thread will continue.
        */
        bool running;

        /**
        * If false, the worker thread hasn't ended.
        */
        bool stopped;

        // Frame calculation. See EntitySystem.h for details.
        int frame_millis;
        int frame_last_millis;
        int elapsed_millis;
        double time_unit;

        /**
         * The maximum frames per second.
         */
        int maxfps;

        /**
         * The worker function.
         */
        FunctionRefPtr function;

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(ParticleWorker);

};

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_PARTICLEWORKER_H_ */
