/*
 * RelationshipInstanceManager.cpp
 *
 *  Created on: 24.01.2015
 *      Author: aschaeffer
 */

#include "RelationshipInstanceManager.h"

namespace inexor {
namespace entity {

RelationshipInstanceManager::RelationshipInstanceManager(CefRefPtr<RelationshipTypeManager> relationship_type_manager)
    : thread(NULL), running(false), stopped(true), maxfps(5), relationship_type_manager(relationship_type_manager)
{
    frame_millis = frame_last_millis = SDL_GetTicks();
}

RelationshipInstanceManager::~RelationshipInstanceManager()
{
}

InstanceRefPtr<RelationshipInstance> RelationshipInstanceManager::CreateInstance(TypeRefPtr<RelationshipType> relationship_type, InstanceRefPtr<EntityInstance> start_node, InstanceRefPtr<EntityInstance> end_node)
{
    InstanceRefPtr<RelationshipInstance> relationship_instance = new RelationshipInstance(relationship_type, start_node, end_node);
    create_instances_mutex.lock();
    create_instances.push_back(relationship_instance);
    create_instances_mutex.unlock();
    start_node->outgoing[relationship_type->uuid].push_back(relationship_instance);
    end_node->incoming[relationship_type->uuid].push_back(relationship_instance);
    // start_node->AddOutgoingRelationship(relationship_type, relationship_instance);
    // end_node->AddIncomingRelationship(relationship_type, relationship_instance);
    return relationship_instance;
}

InstanceRefPtr<RelationshipInstance> RelationshipInstanceManager::CreateInstance(std::string relationship_type_name, InstanceRefPtr<EntityInstance> start_node, InstanceRefPtr<EntityInstance> end_node)
{
    TypeRefPtr<RelationshipType> relationship_type = relationship_type_manager->Get(relationship_type_name);
    return CreateInstance(relationship_type, start_node, end_node);
}

bool RelationshipInstanceManager::Exists(std::string uuid)
{
    return relationship_instances.count(uuid);
}

InstanceRefPtr<RelationshipInstance> RelationshipInstanceManager::Get(std::string uuid)
{
    return relationship_instances[uuid];
}

std::list<InstanceRefPtr<RelationshipInstance> > RelationshipInstanceManager::GetAll(TypeRefPtr<RelationshipType> relationship_type)
{
    // TODO: implement
    // Iterate through all instances and check type (costly)
}

std::list<InstanceRefPtr<RelationshipInstance> > RelationshipInstanceManager::GetAll(std::string relationship_type_name)
{
    TypeRefPtr<RelationshipType> relationship_type = relationship_type_manager->Get(relationship_type_name);
    return GetAll(relationship_type);
}

void RelationshipInstanceManager::DeleteInstance(InstanceRefPtr<RelationshipInstance> instance)
{
    instance->alive = false;
}

void RelationshipInstanceManager::DeleteInstance(std::string uuid)
{
    relationship_instances[uuid]->alive = false;
}

void RelationshipInstanceManager::DeleteAllInstances()
{
    relationship_instances_mutex.lock();
    relationship_instances.clear();
    relationship_instances_mutex.unlock();
}

void RelationshipInstanceManager::DeleteAllInstances(TypeRefPtr<RelationshipType> relationship_type)
{
    relationship_instances_mutex.lock();
    auto it = relationship_instances.begin();
    while (it != relationship_instances.end())
    {
        if (it->second->GetType()->GetUuid() == relationship_type->GetUuid())
        {
            it = relationship_instances.erase(it);
        } else {
            ++it;
        }
    }
    relationship_instances_mutex.unlock();
}

void RelationshipInstanceManager::Invalidate()
{
    relationship_instances_mutex.lock();
    std::unordered_map<std::string, InstanceRefPtr<RelationshipInstance> >::const_iterator it = relationship_instances.begin();
    while (it != relationship_instances.end())
    {
        // InstanceRefPtr<RelationshipInstance> inst = (*it).second;
        if (!(*it).second->alive) {
            (*it).second->startNode->outgoing[(*it).second->type->uuid].remove((*it).second);
            (*it).second->endNode->incoming[(*it).second->type->uuid].remove((*it).second);
            it = relationship_instances.erase(it);
        } else {
            ++it;
        }
    }
    relationship_instances_mutex.unlock();
}

void RelationshipInstanceManager::DoCreateInstances()
{
    // create_instances.push_back(relationship_instance);
    relationship_instances_mutex.lock();
    std::list<InstanceRefPtr<RelationshipInstance> >::const_iterator it = create_instances.begin();
    while (it != create_instances.end())
    {
        relationship_instances[(*it)->uuid] = (*it);
        ++it;
    }
    relationship_instances_mutex.unlock();
    create_instances_mutex.lock();
    create_instances.clear();
    create_instances_mutex.unlock();
}


int RelationshipInstanceManager::Work(void *data)
{
    RelationshipInstanceManager *w = (RelationshipInstanceManager *) data;
    try
    {
        logoutf("RelationshipInstanceManager::Worker thread started");
        w->running = true;
        w->stopped = false;
        while (w->running)
        {
            w->frame_millis = SDL_GetTicks();
            w->LimitFps(w->frame_millis, w->frame_last_millis, w->maxfps);
            w->Invalidate();
            w->DoCreateInstances();
            w->frame_last_millis = w->frame_millis;
        }
    } catch (int e)
    {
        logoutf("RelationshipInstanceManager::Worker died! e: %d", e);
    }
    logoutf("RelationshipInstanceManager::Worker thread stopped");
    return 0;
}

/**
 * Limits the frames per second.
 */
void RelationshipInstanceManager::LimitFps(int &millis, int curmillis, int maxfps)
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

void RelationshipInstanceManager::Start()
{
    if (stopped)
    {
        logoutf("Starting default worker thread RelationshipInstanceManager");
        thread = SDL_CreateThread(Work, "RelationshipInstanceManager", this);
    }
}

void RelationshipInstanceManager::Stop()
{
    if (!stopped)
    {
        running = false;
// SDL_KillThread(thread);
        logoutf("Stopping worker thread RelationshipInstanceManager");
        int retValue;
        SDL_WaitThread(thread, &retValue);
    }
}

int RelationshipInstanceManager::Size() {
    return relationship_instances.size();
}

}
}
