/*
 * EmitterWorker.cpp
 *
 *  Created on: 01.02.2015
 *      Author: aschaeffer
 */

#include "EmitterWorker.h"
#include "../ParticleSubsystem.h"

namespace inexor {
namespace entity {
namespace particle {

EmitterWorker::EmitterWorker(std::string name, FunctionRefPtr function, InstanceRefPtr<EntityInstance> emitter_instance)
    : ParticleWorker(name, function), emitter_instance(emitter_instance)
{
    std::string particle_type_name = emitter_instance->GetAttribute("particle_type")->stringVal;
    particle_type = particle_subsystem->GetParticleType(particle_type_name);
    emitted_by = particle_subsystem->GetRelationshipType(REL_EMITTED_BY);
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

                // Calculate number of batches to emit
                int millistoprocess = w->emitter_instance[MILLIS_TO_PROCESS]->intVal + w->elapsed_millis;
                int batches_to_be_emitted = millistoprocess / w->emitter_instance[RATE]->intVal;
                w->emitter_instance[MILLIS_TO_PROCESS] = millistoprocess % w->emitter_instance[RATE]->intVal;

                // Emit particles
                for (int batch = 0; batch < batches_to_be_emitted; batch++)
                {
                    for (int part = 0; part < w->emitter_instance[BATCH_SIZE]->intVal; part++)
                    {
                        w->function->Execute(time_step, w->particle_type.get(), w->emitter_instance.get());
                    }
                }

                // Time step updates for each particle and remove dead particles
                int alive = 0;
                int died = 0;
                try {
                    std::list<InstanceRefPtr<RelationshipInstance> >::iterator it = w->emitter_instance->incoming[w->emitted_by].begin();
                    while (it != w->emitter_instance->incoming[w->emitted_by].end())
                    {
                        if ((*it)->startNode[REMAINING]->intVal > 0)
                        {
                            // Time step updates
                            (*it)->startNode[LAST_ELAPSED]->intVal = (*it)->startNode[ELAPSED]->intVal;
                            (*it)->startNode[ELAPSED]->intVal += w->elapsed_millis;
                            (*it)->startNode[REMAINING]->intVal -= w->elapsed_millis;
                            ++it;
                            // logoutf("[emi] elapsed: %d remaining: %d", particle["elapsed"]->intVal, particle["remaining"]->intVal);
                            alive++;
                        } else {
                            // TODO: pooling!
                            // Remove the particle side of the relationship (most costly)
                            (*it)->startNode->outgoing[w->emitted_by].remove(*it);
                            // Remove the manager side of the relationship
                            particle_subsystem->DeleteRelationship(*it);
                            // Remove the emitter side of the relationship
                            // std::list is efficient in removing with iterators
                            it = w->emitter_instance->incoming[w->emitted_by].erase(it);
                            died++;
                        }
                    }
                    if (alive > 0 || died > 0) logoutf("[emi] alive: %d died: %d", alive, died);
                } catch (int e) {
                    logoutf("exception emitter worker %d", e);
                }
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

}
}
}
