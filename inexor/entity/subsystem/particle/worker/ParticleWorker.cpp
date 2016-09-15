/*
 * ParticleWorker.cpp
 *
 *  Created on: 31.01.2015
 *      Author: aschaeffer
 */

#include "ParticleWorker.hpp"

namespace inexor {
namespace entity {
namespace particle {

    ParticleWorker::ParticleWorker()
        : thread (NULL), name(""), running (false), stopped (true), maxfps(30), function(NULL)
    {
        ResetTimer();
    }

    ParticleWorker::ParticleWorker(std::string name, int maxfps, FunctionRefPtr function)
        : thread (NULL), name(name), running (false), stopped (true), maxfps(maxfps), function(function)
    {
        ResetTimer();
    }

    ParticleWorker::~ParticleWorker()
    {
        // Just be sure to stop the thread, but shutdown is controlled by ParticleSubsystem
        Stop();
    }

    void ParticleWorker::Start()
    {
        if (stopped)
        {
            logoutf("Starting default worker thread %s", name.c_str());
            thread = SDL_CreateThread(Work, name.c_str(), this);
        }
    }

    void ParticleWorker::Stop()
    {
        if (!stopped)
        {
            running = false;
    // SDL_KillThread(thread);
            logoutf("Stopping worker thread %s", name.c_str());
            int retValue;
            SDL_WaitThread(thread, &retValue);
        }
    }

    int ParticleWorker::Work(void *data)
    {
        ParticleWorker *w = (ParticleWorker *) data;
        try
        {
            w->running = true;
            w->stopped = false;
            logoutf("Worker thread started");
            while (w->running)
            {
                w->frame_millis = SDL_GetTicks();
                w->LimitFps(w->frame_millis, w->frame_last_millis, w->maxfps);
                if (!game::ispaused())
                {
                    w->elapsed_millis = w->frame_millis - w->frame_last_millis;
                    TimeStep time_step(
                        w->elapsed_millis,
                        (double) w->elapsed_millis / w->time_unit,
                        w->time_unit
                    );
                    // Simple worker
                    w->function->Execute(time_step);
                }
                w->frame_last_millis = w->frame_millis;
            }
        } catch (int e)
        {
            logoutf("Worker died! e: %d", e);
        }
        w->stopped = true;
        logoutf("Worker thread stopped");
        return 0;
    }

    std::string ParticleWorker::GetName()
    {
        return name;
    }

    void ParticleWorker::SetFunction(FunctionRefPtr function)
    {
        this->function = function;
    }

    void ParticleWorker::ResetTimer()
    {
        frame_millis = frame_last_millis = SDL_GetTicks();
        elapsed_millis = 0;
        time_unit = 1000.0;
    }

    void ParticleWorker::SetTimeUnit(double time_unit)
    {
        this->time_unit = time_unit;
    }

    /**
     * Limits the frames per second.
     */
    void ParticleWorker::LimitFps(int &millis, int curmillis, int maxfps)
    {
        if(!maxfps) return;
        static int fpserror = 0;
        int delay = 1000 / maxfps - (millis - curmillis);
        if(delay < 0) fpserror = 0;
        else
        {
            fpserror += 1000 % maxfps;
            if(fpserror >= maxfps)
            {
                ++delay;
                fpserror -= maxfps;
            }
            if(delay > 0)
            {
                SDL_Delay(delay);
                millis += delay;
            }
        }
    }

}
}
}
