/*
 * ModifierWorker.cpp
 *
 *  Created on: 01.02.2015
 *      Author: aschaeffer
 */

#include "ModifierWorker.h"
#include "../ParticleSubsystem.h"
#include "../../../EntitySystem.h"

namespace inexor {
namespace entity {
namespace particle {

ModifierWorker::ModifierWorker(std::string name, FunctionRefPtr function, InstanceRefPtr<EntityInstance> modifier_instance)
    : ParticleWorker(name, function), modifier_instance(modifier_instance)
{
    // TODO: analyse function, so that we can use the fitting Worker implementation
    // int signature = function->GetSignature();

    modifies = entity_system->GetRelationshipTypeManager()->Get(REL_MODIFIES);
}

ModifierWorker::~ModifierWorker()
{
}

void ModifierWorker::Start()
{
    if (stopped)
    {
        logoutf("Starting modifier worker thread %s", name.c_str());
        thread = SDL_CreateThread(Work, name.c_str(), this);
    }
}

int ModifierWorker::Work(void *data)
{
    ModifierWorker *w = (ModifierWorker *) data;
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
                TimeStep time_step(w->elapsed_millis, w->time_unit);

                // The modifiers are connected to their particles. Iterate
                // over all relationships of the type modifies to get the
                // particle instances. Then call the modifier function with
                // the modifier and particle instances as arguments.
                int alive = 0;
                int died = 0;
                try {
                    std::list<InstanceRefPtr<RelationshipInstance> >::iterator it = w->modifier_instance->outgoing[w->modifies].begin();
                    while (it != w->modifier_instance->outgoing[w->modifies].end())
                    {
                        if ((*it)->endNode[REMAINING]->intVal > 0)
                        {
                            w->function->Execute(time_step, w->modifier_instance.get(), (*it)->endNode.get());
                            ++it;
                            alive++;
                        } else {
                            // Remove the particle side of the relationship (most costly)
                            (*it)->endNode->incoming[w->modifies].remove(*it);
                            // Remove the manager side of the relationship
                            particle_subsystem->DeleteRelationship(*it);
                            // Remove the modifier side of the relationship
                            // std::list is efficient in removing with iterators
                            it = w->modifier_instance->outgoing[w->modifies].erase(it);
                            died++;
                        }
                    }
                    // if (alive > 0 || died > 0) logoutf("[mod] alive: %d died: %d", alive, died);
                } catch (int e) {
                    logoutf("exception modifier worker %d", e);
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
