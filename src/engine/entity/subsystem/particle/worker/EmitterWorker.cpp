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

EmitterWorker::EmitterWorker(std::string name, int maxfps, FunctionRefPtr function, InstanceRefPtr<EntityInstance> emitter_instance, CefRefPtr<EntityInstanceManager> entity_instance_manager, CefRefPtr<RelationshipInstanceManager> relationship_instance_manager)
    : ParticleWorker(name, maxfps, function),
      emitter_instance(emitter_instance),
      entity_instance_manager(entity_instance_manager),
      relationship_instance_manager(relationship_instance_manager)
{
    std::string particle_type_name = emitter_instance[PARTICLE_TYPE]->stringVal;
    particle_type = particle_subsystem->GetParticleType(particle_type_name);
    emitted_by = particle_subsystem->GetRelationshipType(REL_EMITTED_BY);
    apply_initializer = particle_subsystem->GetRelationshipType(REL_APPLY_INITIALIZER);
    apply_modifier = particle_subsystem->GetRelationshipType(REL_APPLY_MODIFIER);
    apply_renderer = particle_subsystem->GetRelationshipType(REL_APPLY_RENDERER);
    modifies = particle_subsystem->GetRelationshipType(REL_MODIFIES);
    renders = particle_subsystem->GetRelationshipType(REL_RENDERS);
}

EmitterWorker::~EmitterWorker()
{
    Stop();
}

void EmitterWorker::Start()
{
    if (stopped)
    {
        logoutf("Starting emitter worker thread %s", name.c_str());
        thread = SDL_CreateThread(Work, name.c_str(), this);
    }
}

void EmitterWorker::Stop()
{
    if (!stopped)
    {
        running = false;
// SDL_KillThread(thread);
        logoutf("Stopping worker thread %s", name.c_str());
        int retValue;
        SDL_WaitThread(thread, &retValue);
        particle_pool.clear();
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
            w->LimitFps(w->frame_millis, w->frame_last_millis, w->maxfps);

            if (!game::ispaused()) // lieber ein frame auslassen (wird eh wieder "reingeholt")
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
                        // w->function->Execute(time_step, w->particle_type.get(), w->emitter_instance.get());
                        if (w->particle_pool.size() > 0)
                        {
                            // If a particle is available, we make it reusable again
                            // by removing it from the pool and reanimate the
                            // relationships

                            // Fetch particle from pool
                            InstanceRefPtr<EntityInstance> particle_inst = w->particle_pool.back();
                            w->particle_pool.pop_back();
                            particle_inst[ELAPSED] = 0;
                            particle_inst[LAST_ELAPSED] = 0;

                            w->function->Execute(time_step, w->emitter_instance.get(), particle_inst.get());

                            // Reanimate all outgoing relationships
                            for(std::unordered_map<std::string, std::list<InstanceRefPtr<RelationshipInstance> > >::iterator it = particle_inst->outgoing.begin(); it != particle_inst->outgoing.end(); ++it)
                            {
                                for(std::list<InstanceRefPtr<RelationshipInstance> >::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
                                {
                                    (*it2)->alive = true;
                                }
                            }

                            // Reanimate all incoming relationships
                            for(std::unordered_map<std::string, std::list<InstanceRefPtr<RelationshipInstance> > >::iterator it = particle_inst->incoming.begin(); it != particle_inst->incoming.end(); ++it)
                            {
                                for(std::list<InstanceRefPtr<RelationshipInstance> >::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
                                {
                                    (*it2)->alive = true;
                                }
                            }

                            // Call all initializers
                            for(std::list<InstanceRefPtr<RelationshipInstance> >::iterator it = w->emitter_instance->outgoing[w->apply_initializer->uuid].begin(); it != w->emitter_instance->outgoing[w->apply_initializer->uuid].end(); ++it)
                            {
                                (*it)->endNode->GetType()[PARTICLE_INITIALIZER_FUNCTION_ATTRIBUTE_NAME]->functionVal(time_step, w->emitter_instance.get(), (*it)->endNode.get(), particle_inst.get());
                            }

                        } else {
                            // No more particles available in the pool
                            // Create a new particle instance and wire them together

                            InstanceRefPtr<EntityInstance> particle_inst = w->entity_instance_manager->Create(w->particle_type);
                            particle_inst[ELAPSED] = 0;
                            particle_inst[LAST_ELAPSED] = 0;
                            w->function->Execute(time_step, w->emitter_instance.get(), particle_inst.get());

                            // Create a relationship from particle instance to it's origin emitter instance
                            w->relationship_instance_manager->CreateUnmanagedInstance(w->emitted_by, particle_inst, w->emitter_instance);

                            // Create relationships from the modifier instances to the newly created particle instance
                            for(std::list<InstanceRefPtr<RelationshipInstance> >::iterator it = w->emitter_instance->outgoing[w->apply_modifier->uuid].begin(); it != w->emitter_instance->outgoing[w->apply_modifier->uuid].end(); ++it)
                            {
                                w->relationship_instance_manager->CreateUnmanagedInstance(w->modifies, (*it)->endNode, particle_inst);
                            }

                            // Create relationships from the renderer instances to the newly created particle instance
                            for(std::list<InstanceRefPtr<RelationshipInstance> >::iterator it = w->emitter_instance->outgoing[w->apply_renderer->uuid].begin(); it != w->emitter_instance->outgoing[w->apply_renderer->uuid].end(); ++it)
                            {
                                w->relationship_instance_manager->CreateUnmanagedInstance(w->renders, (*it)->endNode, particle_inst);
                            }

                            // Call all initializers
                            for(std::list<InstanceRefPtr<RelationshipInstance> >::iterator it = w->emitter_instance->outgoing[w->apply_initializer->uuid].begin(); it != w->emitter_instance->outgoing[w->apply_initializer->uuid].end(); ++it)
                            {
                                (*it)->endNode->GetType()[PARTICLE_INITIALIZER_FUNCTION_ATTRIBUTE_NAME]->functionVal(time_step, w->emitter_instance.get(), (*it)->endNode.get(), particle_inst.get());
                            }

                        }
                    }
                }

                // Time step updates for each particle and remove dead particles
                try {
                    std::list<InstanceRefPtr<RelationshipInstance> >::iterator it = w->emitter_instance->incoming[w->emitted_by->uuid].begin();
                    while (it != w->emitter_instance->incoming[w->emitted_by->uuid].end())
                    {
                        if ((*it)->alive)
                        {
                            if ((*it)->startNode[REMAINING]->intVal > 0)
                            {
                                // Time step updates
                                (*it)->startNode[LAST_ELAPSED]->intVal = (*it)->startNode[ELAPSED]->intVal;
                                (*it)->startNode[ELAPSED]->intVal += w->elapsed_millis;
                                (*it)->startNode[REMAINING]->intVal -= w->elapsed_millis;
                            } else {
                                (*it)->alive = false;
                                // push particle back to the pool
                                w->particle_pool.push_front((*it)->startNode);
                            }
                        }
                        ++it;
                    }
                } catch (int e) {
                    logoutf("exception emitter worker %d", e);
                }
                w->frame_last_millis = w->frame_millis;
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
