/*
 * ParticleSubsystem.cpp
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#include "ParticleSubsystem.h"

extern CefRefPtr<inexor::entity::HandleSubsystem> handle_subsystem;

namespace inexor {
namespace entity {
namespace particle {

ParticleSubsystem::ParticleSubsystem()
    : SubsystemBase(PARTICLE_SUBSYSTEM),
      maxfps(30)
{
}

ParticleSubsystem::ParticleSubsystem(
    CefRefPtr<EntityTypeManager> entity_type_manager,
    CefRefPtr<EntityInstanceManager> entity_instance_manager,
    CefRefPtr<RelationshipTypeManager> relationship_type_manager,
    CefRefPtr<RelationshipInstanceManager> relationship_instance_manager
) : SubsystemBase(PARTICLE_SUBSYSTEM, entity_type_manager, entity_instance_manager, relationship_type_manager, relationship_instance_manager),
    maxfps(30)
{
    // Create entity type factories
    particle_type_factory = new ParticleTypeFactory(entity_type_manager);
    particle_emitter_type_factory = new ParticleEmitterTypeFactory(entity_type_manager);
    particle_initializer_type_factory = new ParticleInitializerTypeFactory(entity_type_manager);
    particle_modifier_type_factory = new ParticleModifierTypeFactory(entity_type_manager);
    particle_renderer_type_factory = new ParticleRendererTypeFactory(entity_type_manager);

    // Register entity type factories
    entity_type_manager->RegisterFactory(particle_type_factory);
    entity_type_manager->RegisterFactory(particle_emitter_type_factory);
    entity_type_manager->RegisterFactory(particle_initializer_type_factory);
    entity_type_manager->RegisterFactory(particle_modifier_type_factory);
    entity_type_manager->RegisterFactory(particle_renderer_type_factory);

    InitializeModel();
}

ParticleSubsystem::~ParticleSubsystem()
{
}

void ParticleSubsystem::Update(TimeStep time_step)
{
    if (mainmenu)
    {
        std::vector<InstanceRefPtr<EntityInstance> >::iterator it = renderers.begin();
        while (it != renderers.end())
        {
            std::list<InstanceRefPtr<RelationshipInstance> >::iterator it2 = (*it)->outgoing[renders->uuid].begin();
            while (it2 != (*it)->outgoing[renders->uuid].end())
            {
                if ((*it2)->endNode[REMAINING]->intVal <= 0)
                {
                    (*it2)->alive = false;
                }
                ++it2;
            }
            ++it;
        }
    }
}

void ParticleSubsystem::InitializeModel()
{
    // Create graph model: Node types
    TypeRefPtr<EntityType> parent_particle_type = entity_type_manager->Create(ENTTYPE_PARENT_PARTICLE_TYPE, true, true);
    TypeRefPtr<EntityType> parent_emitter_type = entity_type_manager->Create(ENTTYPE_PARENT_EMITTER_TYPE, true, true);
    TypeRefPtr<EntityType> parent_initializer_type = entity_type_manager->Create(ENTTYPE_PARENT_INITIALIZER_TYPE, true, true);
    TypeRefPtr<EntityType> parent_modifier_type = entity_type_manager->Create(ENTTYPE_PARENT_MODIFIER_TYPE, true, true);
    TypeRefPtr<EntityType> parent_renderer_type = entity_type_manager->Create(ENTTYPE_PARENT_RENDERER_TYPE, true, true);

    // Create graph model: Relationship types
    emitted_by = relationship_type_manager->Create(REL_EMITTED_BY, false, false, parent_particle_type, parent_emitter_type);
    modifies = relationship_type_manager->Create(REL_MODIFIES, false, false, parent_modifier_type, parent_particle_type);
    renders = relationship_type_manager->Create(REL_RENDERS, false, false, parent_renderer_type, parent_particle_type);
    apply_initializer = relationship_type_manager->Create(REL_APPLY_INITIALIZER, true, true, parent_emitter_type, parent_initializer_type);
    apply_modifier = relationship_type_manager->Create(REL_APPLY_MODIFIER, true, true, parent_emitter_type, parent_modifier_type);
    apply_renderer = relationship_type_manager->Create(REL_APPLY_RENDERER, true, true, parent_emitter_type, parent_renderer_type);

    logoutf("Particle subsystem graph model initialized");
}

void ParticleSubsystem::Cleanup()
{
    // Stop default workers
    for (unsigned int i = 0; i < particle_workers.size(); i++)
    {
        particle_workers[i]->Stop();
    }
    // Stop emitter workers
    for (unsigned int i = 0; i < emitter_workers.size(); i++)
    {
        emitter_workers[i]->Stop();
    }
    // Stop modifier workers
    for (unsigned int i = 0; i < modifier_workers.size(); i++)
    {
        modifier_workers[i]->Stop();
    }

    // TODO: 1. remove renderers
    // TODO: 2. remove instances
    // TODO: 3. remove types

    // Recreate the graph model
    InitializeModel();
}

void ParticleSubsystem::Reset()
{
}

void ParticleSubsystem::RenderFaces()
{
    // TODO: Implement
}

void ParticleSubsystem::RenderParticles()
{
    std::vector<InstanceRefPtr<EntityInstance> >::iterator it = renderers.begin();
    while (it != renderers.end())
    {
        std::list<InstanceRefPtr<RelationshipInstance> >::iterator it2 = (*it)->outgoing[renders->uuid].begin();
        TimeStep time_step(0.0, 1000.0);
        FunctionRefPtr function = (*it)->GetType()[PARTICLE_RENDERER_FUNCTION_ATTRIBUTE_NAME]->functionVal;
        function->Before(time_step, (*it).get());
        while (it2 != (*it)->outgoing[renders->uuid].end())
        {
            if ((*it2)->alive && (*it2)->endNode[REMAINING]->intVal > 0)
            {
                function->Execute(time_step, (*it).get(), (*it2)->endNode.get());
            } else {
                (*it2)->alive = false;
            }
            ++it2;
        }
        function->After(time_step, (*it).get());
        ++it;
    }
}

TypeRefPtr<EntityType> ParticleSubsystem::CreateParticleType(std::string particle_type_name, std::string renderer_instance_name)
{
    TypeRefPtr<EntityType> particle_type = particle_type_factory->Create(particle_type_name, renderer_instance_name);
    particle_types[particle_type->GetName()] = particle_type;
    return particle_type;
}

TypeRefPtr<EntityType> ParticleSubsystem::CreateEmitterType(std::string emitter_type_name, FunctionRefPtr function, TypeRefPtr<EntityType> particle_type, int rate, int batch_size, int lifetime, double mass, double density)
{
    return CreateEmitterType(emitter_type_name, function, particle_type->GetName(), rate, batch_size, lifetime, mass, density);
}

TypeRefPtr<EntityType> ParticleSubsystem::CreateEmitterType(std::string emitter_type_name, FunctionRefPtr function, TypeRefPtr<EntityType> particle_type, int rate, int lifetime)
{
    return CreateEmitterType(emitter_type_name, function, particle_type->GetName(), rate, 1, lifetime, 1.0, 1.0);
}

TypeRefPtr<EntityType> ParticleSubsystem::CreateEmitterType(std::string emitter_type_name, FunctionRefPtr function, std::string particle_type_name, int rate, int batch_size, int lifetime, double mass, double density)
{
    TypeRefPtr<EntityType> emitter_type = particle_emitter_type_factory->Create(emitter_type_name, function, particle_type_name, rate, batch_size, lifetime, mass, density);
    emitter_types[emitter_type->GetName()] = emitter_type;
    return emitter_type;
}

TypeRefPtr<EntityType> ParticleSubsystem::CreateInitializerType(std::string initializer_type_name, FunctionRefPtr function)
{
    TypeRefPtr<EntityType> initializer_type = particle_initializer_type_factory->Create(initializer_type_name, function);
    initializer_types[initializer_type->GetName()] = initializer_type;
    return initializer_type;
}

TypeRefPtr<EntityType> ParticleSubsystem::CreateModifierType(std::string modifier_type_name, FunctionRefPtr function)
{
    TypeRefPtr<EntityType> modifier_type = particle_modifier_type_factory->Create(modifier_type_name, function);
    modifier_types[modifier_type->GetName()] = modifier_type;
    return modifier_type;
}

TypeRefPtr<EntityType> ParticleSubsystem::CreateRendererType(std::string renderer_type_name, FunctionRefPtr function)
{
    TypeRefPtr<EntityType> renderer_type = particle_renderer_type_factory->Create(renderer_type_name, function);
    renderer_types[renderer_type->GetName()] = renderer_type;
    return renderer_type;
}

TypeRefPtr<EntityType> ParticleSubsystem::GetParticleType(std::string particle_type_name)
{
    return particle_types[particle_type_name];
}

TypeRefPtr<EntityType> ParticleSubsystem::GetEmitterType(std::string emitter_type_name)
{
    return emitter_types[emitter_type_name];
}

TypeRefPtr<EntityType> ParticleSubsystem::GetInitializerType(std::string initializer_type_name)
{
    return initializer_types[initializer_type_name];
}

TypeRefPtr<EntityType> ParticleSubsystem::GetModifierType(std::string modifier_type_name)
{
    return modifier_types[modifier_type_name];
}

TypeRefPtr<EntityType> ParticleSubsystem::GetRendererType(std::string renderer_type_name)
{
    return renderer_types[renderer_type_name];
}

TypeRefPtr<RelationshipType> ParticleSubsystem::GetRelationshipType(std::string relationship_type_name)
{
    return relationship_type_manager->Get(relationship_type_name);
}

InstanceRefPtr<EntityInstance> ParticleSubsystem::CreateEmitterInstance(std::string emitter_type_name, double x, double y, double z, double vx, double vy, double vz)
{
    TypeRefPtr<EntityType> emitter_type = entity_type_manager->Get(emitter_type_name);
    return CreateEmitterInstance(emitter_type, x, y, z, vx, vy, vz);
}

InstanceRefPtr<EntityInstance> ParticleSubsystem::CreateEmitterInstance(TypeRefPtr<EntityType> emitter_type, double x, double y, double z, double vx, double vy, double vz)
{
    InstanceRefPtr<EntityInstance> emitter_instance = entity_instance_manager->Create(emitter_type);

    // Assign defaults from emitter type
    emitter_instance[PARTICLE_TYPE] = emitter_type[PARTICLE_TYPE]->stringVal;
    emitter_instance[RATE] = emitter_type[RATE]->intVal;
    emitter_instance[BATCH_SIZE] = emitter_type[BATCH_SIZE]->intVal;
    emitter_instance[LIFETIME] = emitter_type[LIFETIME]->intVal;
    emitter_instance[MASS] = emitter_type[MASS]->doubleVal;
    emitter_instance[DENSITY] = emitter_type[DENSITY]->doubleVal;

    // Set initial position and velocity
    emitter_instance[POS] = vec(x, y, z);
    emitter_instance[VELOCITY] = vec(vx, vy, vz);

    // The millis to process
    emitter_instance[MILLIS_TO_PROCESS] = 0;

    // Enable the emitter instance
    emitter_instance[ENABLED] = true;

    // Starts the worker thread for the emitter instance (which also calls the connected initializer instances)
    CreateEmitterWorker(emitter_type, emitter_instance);

    // Create an handle for the emitter and connect them
    InstanceRefPtr<EntityInstance> handle = handle_subsystem->CreateHandle(emitter_instance);
    handle[DIR] = vec(vx, vy, vz);

    return emitter_instance;
}

InstanceRefPtr<EntityInstance> ParticleSubsystem::CreateInitializerInstance(std::string initializer_type_name)
{
    TypeRefPtr<EntityType> initializer_type = entity_type_manager->Get(initializer_type_name);
    return CreateInitializerInstance(initializer_type);
}

InstanceRefPtr<EntityInstance> ParticleSubsystem::CreateInitializerInstance(TypeRefPtr<EntityType> initializer_type)
{
    InstanceRefPtr<EntityInstance> initializer_instance = entity_instance_manager->Create(initializer_type);
    return initializer_instance;
}

InstanceRefPtr<EntityInstance> ParticleSubsystem::CreateModifierInstance(std::string modifier_type_name)
{
    TypeRefPtr<EntityType> modifier_type = entity_type_manager->Get(modifier_type_name);
    return CreateModifierInstance(modifier_type);
}

InstanceRefPtr<EntityInstance> ParticleSubsystem::CreateModifierInstance(TypeRefPtr<EntityType> modifier_type)
{
    InstanceRefPtr<EntityInstance> modifier_instance = entity_instance_manager->Create(modifier_type);

    // Assign defaults from modifier type
    // modifier_instance["particle_type"] = modifier_type["particle_type"]->stringVal;

    // Set initial position and velocity
    // modifier_instance["x"] = x;

    // TODO: maybe copy attributes from the modifier type to the modifier instance, if a flag is set to do so
    // -> New flag in EntityAttribute "initializes_instance"
    // -> Iterate over all attributes and copy it

    // The millis to process
    modifier_instance[MILLIS_TO_PROCESS] = 0;

    // Enable the modifier instance
    modifier_instance[ENABLED] = true;

    // Starts the worker thread for the modifier instance
    CreateModifierWorker(modifier_type, modifier_instance);

    return modifier_instance;
}

InstanceRefPtr<EntityInstance> ParticleSubsystem::CreateRendererInstance(std::string renderer_type_name, std::string model, vec offset)
{
    TypeRefPtr<EntityType> renderer_type = entity_type_manager->Get(renderer_type_name);
    return CreateRendererInstance(renderer_type, model, offset);
}

InstanceRefPtr<EntityInstance> ParticleSubsystem::CreateRendererInstance(std::string renderer_type_name, std::string shader, std::string texture, float size)
{
    TypeRefPtr<EntityType> renderer_type = entity_type_manager->Get(renderer_type_name);
    return CreateRendererInstance(renderer_type, shader, texture, size);
}

InstanceRefPtr<EntityInstance> ParticleSubsystem::CreateRendererInstance(TypeRefPtr<EntityType> renderer_type, std::string model, vec offset)
{
    InstanceRefPtr<EntityInstance> renderer_instance = entity_instance_manager->Create(renderer_type);

    // Sets the shader name
    renderer_instance[SHADER] = "";

    // Sets the texture name
    renderer_instance[TEXTURE] = "";

    // Sets the model
    renderer_instance[MODEL] = model;

    // Sets the size
    renderer_instance[SIZE] = 1.0f;

    // Sets the offset
    renderer_instance[OFFSET] = vec(offset);

    renderers.push_back(renderer_instance);
    return renderer_instance;
}

InstanceRefPtr<EntityInstance> ParticleSubsystem::CreateRendererInstance(TypeRefPtr<EntityType> renderer_type, std::string shader, std::string texture, float size)
{
    InstanceRefPtr<EntityInstance> renderer_instance = entity_instance_manager->Create(renderer_type);

    // Sets the shader name
    renderer_instance[SHADER] = shader;

    // Sets the texture name
    renderer_instance[TEXTURE] = texture;

    // Sets the model
    renderer_instance[MODEL] = "";

    // Sets the size
    renderer_instance[SIZE] = size;

    // Sets the offset
    renderer_instance[OFFSET] = vec(0.0f, 0.0f, 0.0f);

    renderers.push_back(renderer_instance);
    return renderer_instance;
}

void ParticleSubsystem::DestroyEmitterInstance(std::string uuid)
{
    InstanceRefPtr<EntityInstance> emitter_instance = entity_instance_manager->Get(uuid);
    DestroyEmitterInstance(emitter_instance);
}

void ParticleSubsystem::DestroyEmitterInstance(InstanceRefPtr<EntityInstance> emitter_instance)
{
    // Stop worker
    DestroyEmitterWorker(emitter_instance);
    // Remove emitter
    entity_instance_manager->DeleteInstance(emitter_instance);
}

void ParticleSubsystem::DestroyInitializerInstance(std::string uuid)
{
    InstanceRefPtr<EntityInstance> initializer_instance = entity_instance_manager->Get(uuid);
    DestroyInitializerInstance(initializer_instance);
}

void ParticleSubsystem::DestroyInitializerInstance(InstanceRefPtr<EntityInstance> initializer_instance)
{
    // Remove initializer
    entity_instance_manager->DeleteInstance(initializer_instance);
}

void ParticleSubsystem::DestroyModifierInstance(std::string uuid)
{
    InstanceRefPtr<EntityInstance> modifier_instance = entity_instance_manager->Get(uuid);
    DestroyModifierInstance(modifier_instance);
}

void ParticleSubsystem::DestroyModifierInstance(InstanceRefPtr<EntityInstance> modifier_instance)
{
    // Stop worker
    DestroyModifierWorker(modifier_instance);
    // Remove modifier
    entity_instance_manager->DeleteInstance(modifier_instance);
}

void ParticleSubsystem::DestroyRendererInstance(std::string uuid)
{
    InstanceRefPtr<EntityInstance> renderer_instance = entity_instance_manager->Get(uuid);
    DestroyRendererInstance(renderer_instance);
}

void ParticleSubsystem::DestroyRendererInstance(InstanceRefPtr<EntityInstance> renderer_instance)
{
    // Remove renderer
    entity_instance_manager->DeleteInstance(renderer_instance);
}

InstanceRefPtr<RelationshipInstance> ParticleSubsystem::AddModifierToEmitter(InstanceRefPtr<EntityInstance> emitter_instance, InstanceRefPtr<EntityInstance> modifier_instance)
{
    if (apply_modifier.get()) {
        InstanceRefPtr<RelationshipInstance> relationship_instance = relationship_instance_manager->CreateInstance(apply_modifier, emitter_instance, modifier_instance);
        return relationship_instance;
    } else {
        return NULL;
    }
}

InstanceRefPtr<RelationshipInstance> ParticleSubsystem::AddInitializerToEmitter(InstanceRefPtr<EntityInstance> emitter_instance, InstanceRefPtr<EntityInstance> initializer_instance)
{
    if (apply_initializer.get()) {
        InstanceRefPtr<RelationshipInstance> relationship_instance = relationship_instance_manager->CreateInstance(apply_initializer, emitter_instance, initializer_instance);
        return relationship_instance;
    } else {
        return NULL;
    }
}

InstanceRefPtr<RelationshipInstance> ParticleSubsystem::AddRendererToEmitter(InstanceRefPtr<EntityInstance> emitter_instance, InstanceRefPtr<EntityInstance> renderer_instance)
{
    if (apply_renderer.get()) {
        InstanceRefPtr<RelationshipInstance> relationship_instance = relationship_instance_manager->CreateInstance(apply_renderer, emitter_instance, renderer_instance);
        return relationship_instance;
    } else {
        return NULL;
    }
}

CefRefPtr<ParticleWorker> ParticleSubsystem::CreateParticleWorker(std::string name, FunctionRefPtr function)
{
    return CreateParticleWorker(name, function, maxfps);
}

CefRefPtr<ParticleWorker> ParticleSubsystem::CreateParticleWorker(std::string name, FunctionRefPtr function, int maxfps)
{
    CefRefPtr<ParticleWorker> worker = new ParticleWorker(name, maxfps, function);
    particle_workers.push_back(worker);
    worker->Start();
    return worker;
}

CefRefPtr<EmitterWorker> ParticleSubsystem::CreateEmitterWorker(TypeRefPtr<EntityType> emitter_type, InstanceRefPtr<EntityInstance> emitter_instance)
{
    return CreateEmitterWorker(emitter_type, emitter_instance, maxfps);
}

CefRefPtr<EmitterWorker> ParticleSubsystem::CreateEmitterWorker(TypeRefPtr<EntityType> emitter_type, InstanceRefPtr<EntityInstance> emitter_instance, int maxfps)
{
    FunctionRefPtr function = emitter_type->GetAttribute(PARTICLE_EMITTER_FUNCTION_ATTRIBUTE_NAME)->GetFunction();
    std::string thread_name = emitter_type->GetName() + "_" + emitter_instance->uuid;
    CefRefPtr<EmitterWorker> worker = new EmitterWorker(thread_name, maxfps, function, emitter_instance, entity_instance_manager, relationship_instance_manager);
    emitter_workers.push_back(worker);
    worker->Start();
    return worker;
}

CefRefPtr<ModifierWorker> ParticleSubsystem::CreateModifierWorker(TypeRefPtr<EntityType> modifier_type, InstanceRefPtr<EntityInstance> modifier_instance)
{
    return CreateModifierWorker(modifier_type, modifier_instance, maxfps);
}

CefRefPtr<ModifierWorker> ParticleSubsystem::CreateModifierWorker(TypeRefPtr<EntityType> modifier_type, InstanceRefPtr<EntityInstance> modifier_instance, int maxfps)
{
    FunctionRefPtr function = modifier_type->GetAttribute(PARTICLE_MODIFIER_FUNCTION_ATTRIBUTE_NAME)->GetFunction();
    std::string thread_name = modifier_type->GetName() + "_" + modifier_instance->uuid;
    CefRefPtr<ModifierWorker> worker = new ModifierWorker(thread_name, maxfps, function, modifier_instance, entity_instance_manager, relationship_instance_manager);
    modifier_workers.push_back(worker);
    worker->Start();
    return worker;
}

void ParticleSubsystem::DestroyParticleWorker(std::string name)
{
    for (unsigned int i = 0; i < particle_workers.size(); i++)
    {
        if (particle_workers[i]->GetName() == name) {
            particle_workers[i]->Stop();
            return;
        }
    }
}

void ParticleSubsystem::DestroyParticleWorker(InstanceRefPtr<EntityInstance> entity_instance)
{
    for (unsigned int i = 0; i < particle_workers.size(); i++)
    {
        if (particle_workers[i]->GetName() == entity_instance->uuid) {
            particle_workers[i]->Stop();
            break;
        }
    }
    for (unsigned int i = 0; i < emitter_workers.size(); i++)
    {
        if (emitter_workers[i]->GetName() == entity_instance->uuid) {
            emitter_workers[i]->Stop();
            break;
        }
    }
    for (unsigned int i = 0; i < modifier_workers.size(); i++)
    {
        if (modifier_workers[i]->GetName() == entity_instance->uuid) {
            modifier_workers[i]->Stop();
            break;
        }
    }
}

void ParticleSubsystem::DestroyEmitterWorker(InstanceRefPtr<EntityInstance> emitter_instance)
{
    for (unsigned int i = 0; i < emitter_workers.size(); i++)
    {
        if (emitter_workers[i]->GetName() == emitter_instance->uuid) {
            emitter_workers[i]->Stop();
            return;
        }
    }
}

void ParticleSubsystem::DestroyModifierWorker(InstanceRefPtr<EntityInstance> modifier_instance)
{
    for (unsigned int i = 0; i < modifier_workers.size(); i++)
    {
        if (modifier_workers[i]->GetName() == modifier_instance->uuid) {
            modifier_workers[i]->Stop();
            return;
        }
    }
}

}
}
}
