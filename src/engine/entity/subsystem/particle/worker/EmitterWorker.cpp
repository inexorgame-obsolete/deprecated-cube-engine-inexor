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
                            // Fetch particle from pool
                            InstanceRefPtr<EntityInstance> particle_inst = w->particle_pool.back();
                            w->particle_pool.pop_back();
                            particle_inst[ELAPSED] = 0;
                            particle_inst[LAST_ELAPSED] = 0;
                            particle_inst->incoming.clear();
                            particle_inst->outgoing.clear();
                            w->function->Execute(time_step, w->emitter_instance.get(), particle_inst.get());

                            // Create relationship from particle to emitter
                            w->relationship_instance_manager->CreateInstance(
                                // The relationship type
                                w->emitted_by,
                                // Start node: The particle instance
                                particle_inst,
                                // End node: The emitter instance
                                w->emitter_instance
                            );

                            // Call all initializers
                            for(std::list<InstanceRefPtr<RelationshipInstance> >::iterator it = w->emitter_instance->outgoing[w->apply_initializer->uuid].begin(); it != w->emitter_instance->outgoing[w->apply_initializer->uuid].end(); ++it)
                            {
                                (*it)->endNode->GetType()[PARTICLE_INITIALIZER_FUNCTION_ATTRIBUTE_NAME]->functionVal(time_step, w->emitter_instance.get(), (*it)->endNode.get(), particle_inst.get());
                            }

                            // The emitter instance has relationships to modifiers:
                            //
                            //     emitter--[:apply_modifier]-->modifier
                            //
                            // This means that each of these connected modifiers should be applied
                            // on the newly created particle. Therefore we connect the newly created
                            // particle with the modifier:
                            //
                            //     modifier--[:modifies]-->particle
                            //
                            for(std::list<InstanceRefPtr<RelationshipInstance> >::iterator it = w->emitter_instance->outgoing[w->apply_modifier->uuid].begin(); it != w->emitter_instance->outgoing[w->apply_modifier->uuid].end(); ++it)
                            {
                                w->relationship_instance_manager->CreateInstance(
                                    // The relationship type
                                    w->modifies,
                                    // Start node: The modifier instance (which is the end node of the
                                    // apply_modifiers relationship)
                                    (*it)->endNode,
                                    // End node: The particle instance
                                    particle_inst
                                );
                            }

                            // Create relationship from the renderer instance to the newly created particle instance
                            for(std::list<InstanceRefPtr<RelationshipInstance> >::iterator it = w->emitter_instance->outgoing[w->apply_renderer->uuid].begin(); it != w->emitter_instance->outgoing[w->apply_renderer->uuid].end(); ++it)
                            {
                                w->relationship_instance_manager->CreateInstance(
                                    // The relationship type
                                    w->renders,
                                    // Start node: The renderer instance (which is the end node of the
                                    // apply_renderers relationship)
                                    (*it)->endNode,
                                    // End node: The particle instance
                                    particle_inst
                                );
                            }

                        } else {
                            // Create new instance
                            InstanceRefPtr<EntityInstance> particle_inst = w->entity_instance_manager->Create(w->particle_type);
                            particle_inst[ELAPSED] = 0;
                            particle_inst[LAST_ELAPSED] = 0;
                            w->function->Execute(time_step, w->emitter_instance.get(), particle_inst.get());

                            // Create relationship from particle to emitter
                            w->relationship_instance_manager->CreateInstance(
                                // The relationship type
                                w->emitted_by,
                                // Start node: The particle instance
                                particle_inst,
                                // End node: The emitter instance
                                w->emitter_instance
                            );

                            // Call all initializers
                            for(std::list<InstanceRefPtr<RelationshipInstance> >::iterator it = w->emitter_instance->outgoing[w->apply_initializer->uuid].begin(); it != w->emitter_instance->outgoing[w->apply_initializer->uuid].end(); ++it)
                            {
                                (*it)->endNode->GetType()[PARTICLE_INITIALIZER_FUNCTION_ATTRIBUTE_NAME]->functionVal(time_step, w->emitter_instance.get(), (*it)->endNode.get(), particle_inst.get());
                            }

                            // The emitter instance has relationships to modifiers:
                            //
                            //     emitter--[:apply_modifier]-->modifier
                            //
                            // This means that each of these connected modifiers should be applied
                            // on the newly created particle. Therefore we connect the newly created
                            // particle with the modifier:
                            //
                            //     modifier--[:modifies]-->particle
                            //
                            for(std::list<InstanceRefPtr<RelationshipInstance> >::iterator it = w->emitter_instance->outgoing[w->apply_modifier->uuid].begin(); it != w->emitter_instance->outgoing[w->apply_modifier->uuid].end(); ++it)
                            {
                                w->relationship_instance_manager->CreateInstance(
                                    // The relationship type
                                    w->modifies,
                                    // Start node: The modifier instance (which is the end node of the
                                    // apply_modifiers relationship)
                                    (*it)->endNode,
                                    // End node: The particle instance
                                    particle_inst
                                );
                            }

                            // Create relationship from the renderer instance to the newly created particle instance
                            for(std::list<InstanceRefPtr<RelationshipInstance> >::iterator it = w->emitter_instance->outgoing[w->apply_renderer->uuid].begin(); it != w->emitter_instance->outgoing[w->apply_renderer->uuid].end(); ++it)
                            {
                                w->relationship_instance_manager->CreateInstance(
                                    // The relationship type
                                    w->renders,
                                    // Start node: The renderer instance (which is the end node of the
                                    // apply_renderers relationship)
                                    (*it)->endNode,
                                    // End node: The particle instance
                                    particle_inst
                                );
                            }


                        }
                    }
                }

                // Time step updates for each particle and remove dead particles
                try {
                    // w->relationship_instance_manager->relationship_instances_mutex.lock();
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
                                w->particle_pool.push_front((*it)->startNode);
                            }
                        }
                        ++it;
                    }
                    // w->relationship_instance_manager->relationship_instances_mutex.unlock();
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
