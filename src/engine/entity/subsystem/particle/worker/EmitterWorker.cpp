/*
 * EmitterWorker.cpp
 *
 *  Created on: 01.02.2015
 *      Author: aschaeffer
 */

#include "EmitterWorker.h"
#include "../ParticleSubsystem.h"

EmitterWorker::EmitterWorker(std::string name, FunctionRefPtr function, InstanceRefPtr<EntityInstance> emitter_instance)
    : emitter_instance(emitter_instance), ParticleWorker(name, function)
{
    std::string particle_type_name = emitter_instance->GetAttribute("particle_type")->stringVal;
    particle_type = particle_subsystem->GetParticleType(particle_type_name);
    // logoutf("EmitterWorker::EmitterWorker particle type Name: %s UUID: %s", particle_type_name.c_str(), particle_type->GetUuid().c_str());
    // logoutf("EmitterWorker::EmitterWorker emitter instance UUID: %s", emitter_instance->GetUuid().c_str());
}

EmitterWorker::~EmitterWorker()
{
}

void EmitterWorker::Start()
{
    if (stopped)
    {
        logoutf("Starting emitter worker thread %s", name.c_str());
        thread = SDL_CreateThread(Work, name.c_str(), this);
    }
}

int EmitterWorker::Work(void *data)
{
    EmitterWorker *w = (EmitterWorker *) data;
    try
    {
        w->running = true;
        w->stopped = false;
        logoutf("Worker thread started");
        while (w->running)
        {
            w->frame_millis = SDL_GetTicks();
            limitfps(w->frame_millis, w->frame_last_millis);
            if (!game::ispaused())
            {
                w->elapsed_millis = w->frame_millis - w->frame_last_millis;
                TimeStep time_step(
                    w->elapsed_millis,
                    (double) w->elapsed_millis / w->time_unit,
                    w->time_unit
                );

                int millistoprocess = w->emitter_instance["millistoprocess"]->intVal + w->elapsed_millis;
                int batches_to_be_emitted = millistoprocess / w->emitter_instance["rate"]->intVal;
                w->emitter_instance["millistoprocess"] = millistoprocess % w->emitter_instance["rate"]->intVal;

                for (int batch = 0; batch < batches_to_be_emitted; batch++)
                {
                    w->function->Execute(time_step, w->particle_type.get(), w->emitter_instance.get());
                }
//                logoutf("EmitterWorker::Work() elapsed_millis: %d time_factor: %2.3f time_unit: %4.1f", time_step.elapsed_millis, time_step.time_factor, time_step.time_unit);
//                logoutf("Emitter Instance UUID: %s",w->emitter_instance->GetUuid().c_str());
//                logoutf("Particle Type Name: %s UUID: %s", w->particle_type->GetName().c_str(), w->particle_type->GetUuid().c_str());
//                w->function->Execute(time_step, w->particle_type.get(), w->emitter_instance.get());
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
