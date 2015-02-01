/*
 * ModifierWorker.cpp
 *
 *  Created on: 01.02.2015
 *      Author: aschaeffer
 */

#include "ModifierWorker.h"
#include "../ParticleSubsystem.h"
#include "../../../EntitySystem.h"

ModifierWorker::ModifierWorker(std::string name, FunctionRefPtr function, InstanceRefPtr<EntityInstance> modifier_instance)
    : modifier_instance(modifier_instance), ParticleWorker(name, function)
{
    // TODO: analyse function, so that we can use the fitting Worker implementation
    int signature = function->GetSignature();

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
                std::list<InstanceRefPtr<RelationshipInstance> > modifies = w->modifier_instance->GetAllOutgoingRelationshipsOfType(w->modifies);
                for(std::list<InstanceRefPtr<RelationshipInstance> >::iterator it = modifies.begin(); it != modifies.end(); ++it)
                {
                    w->function->Execute(time_step, w->modifier_instance.get(), (*it)->GetEndNode().get());
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
