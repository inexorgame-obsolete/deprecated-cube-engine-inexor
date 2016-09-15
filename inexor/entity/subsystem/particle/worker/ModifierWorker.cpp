/*
 * ModifierWorker.cpp
 *
 *  Created on: 01.02.2015
 *      Author: aschaeffer
 */

#include "ModifierWorker.hpp"
#include "../ParticleSubsystem.hpp"
#include "../../../EntitySystem.hpp"

namespace inexor {
namespace entity {
namespace particle {

    ModifierWorker::ModifierWorker(std::string name, int maxfps, FunctionRefPtr function, InstanceRefPtr<EntityInstance> modifier_instance, CefRefPtr<EntityInstanceManager> entity_instance_manager, CefRefPtr<RelationshipInstanceManager> relationship_instance_manager)
        : ParticleWorker(name, maxfps, function),
          modifier_instance(modifier_instance),
          entity_instance_manager(entity_instance_manager),
          relationship_instance_manager(relationship_instance_manager)
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
                w->LimitFps(w->frame_millis, w->frame_last_millis, w->maxfps);

                if (/* w->relationship_instance_manager->relationship_instances_mutex.try_lock() && */ !game::ispaused()) // lieber ein frame auslassen (wird eh wieder "reingeholt")
                {
                    w->elapsed_millis = w->frame_millis - w->frame_last_millis;
                    TimeStep time_step(w->elapsed_millis, w->time_unit);

                    // The modifiers are connected to their particles. Iterate
                    // over all relationships of the type modifies to get the
                    // particle instances. Then call the modifier function with
                    // the modifier and particle instances as arguments.
                    try {
                        std::list<InstanceRefPtr<RelationshipInstance> >::iterator it = w->modifier_instance->outgoing[w->modifies->uuid].begin();
                        w->function->Before(time_step, w->modifier_instance.get());
                        while (it != w->modifier_instance->outgoing[w->modifies->uuid].end())
                        {
                            if ((*it)->alive && (*it)->endNode[REMAINING]->intVal > 0)
                            {
                                w->function->Execute(time_step, w->modifier_instance.get(), (*it)->endNode.get());
                            } else {
                                (*it)->alive = false;
                            }
                            ++it;
                        }
                        w->function->After(time_step, w->modifier_instance.get());
                    } catch (int e) {
                        logoutf("exception modifier worker %d", e);
                    }
                    w->frame_last_millis = w->frame_millis;
                    // w->relationship_instance_manager->relationship_instances_mutex.unlock();
                }
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
