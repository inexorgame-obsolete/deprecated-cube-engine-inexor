/*
 * RelationshipInstanceManager.h
 *
 *  Created on: 24.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_RELATIONSHIPINSTANCEMANAGER_H_
#define SRC_ENGINE_ENTITY_RELATIONSHIPINSTANCEMANAGER_H_

#include <mutex>

#include "RelationshipTypeManager.h"
#include "../domain/InstanceRefPtr.h"
#include "../domain/TypeRefPtr.h"
#include "../EntitySystemBase.h"
#include "../domain/graph/RelationshipInstance.h"
#include "../domain/graph/RelationshipType.h"

namespace inexor {
namespace entity {

/**
 * The relationship instance manager is the central management service for
 * relationship instances. The complete lifecycle (create, delete) of a
 * relationship is managed by this class.
 */
class RelationshipInstanceManager
{
    public:
        RelationshipInstanceManager(CefRefPtr<RelationshipTypeManager> relationship_type_manager);
        virtual ~RelationshipInstanceManager();

        InstanceRefPtr<RelationshipInstance> CreateInstance(TypeRefPtr<RelationshipType> relationship_type, InstanceRefPtr<EntityInstance> start_node, InstanceRefPtr<EntityInstance> end_node);
        InstanceRefPtr<RelationshipInstance> CreateInstance(std::string relationship_type_name, InstanceRefPtr<EntityInstance> start_node, InstanceRefPtr<EntityInstance> end_node);

        bool Exists(std::string uuid);
        InstanceRefPtr<RelationshipInstance> Get(std::string uuid);
        std::list<InstanceRefPtr<RelationshipInstance> > GetAll(TypeRefPtr<RelationshipType> relationship_type);
        std::list<InstanceRefPtr<RelationshipInstance> > GetAll(std::string relationship_type_name);

        /**
         * Does only remove the relationship from this instance manager.
         * @param instance The relationship instance.
         */
        void DeleteInstance(InstanceRefPtr<RelationshipInstance> instance);

        /**
         * Does only remove the relationship from this instance manager.
         * @param uuid The unique identifier of the relationship instance.
         */
        void DeleteInstance(std::string uuid);

        void DeleteAllInstances();
        void DeleteAllInstances(TypeRefPtr<RelationshipType> relationship_type);

        /**
         * Cleanup of all invalidated / dead relationships. Removes all
         * relationships that are no more alive. This is done to ensure that
         * the relationships are removed in a thread safe way. During this
         * manager is "locked", no modification should happen!
         */
        void Invalidate();
        void DoCreateInstances();

        /**
         * Starts the thread. Overwrite this in custom workers.
         */
        virtual void Start();

        /**
         * Stops the thread.
         */
        void Stop();

        int Size();

        /**
         * A mutex
         */
        std::mutex relationship_instances_mutex;

    private:

        /**
         * Worker thread for cleanup invalid instances and creating new
         * instances.
         */
        static int Work(void *data);

        /**
         * Limits the frames per second.
         */
        void LimitFps(int &millis, int curmillis, int maxfps);

        /**
        * The worker thread.
        */
        SDL_Thread *thread;

        /**
        * If true, the worker thread will continue.
        */
        bool running;

        /**
        * If false, the worker thread hasn't ended.
        */
        bool stopped;

        // Frame calculation. See EntitySystem.h for details.
        int frame_millis;
        int frame_last_millis;

        /**
         * The maximum frames per second.
         */
        int maxfps;

        /**
         * The relationship instances. Don't insert directly. Instead use the
         * CreateInstance methods which buffers the insertions and is lock
         * protected.
         */
        std::unordered_map<std::string, InstanceRefPtr<RelationshipInstance> > relationship_instances;

        /**
         * List of instances to be created. This happens asynchronously and
         * is lock protected.
         */
        std::list<InstanceRefPtr<RelationshipInstance> > create_instances;
        std::mutex create_instances_mutex;

        // The relationship type manager.
        CefRefPtr<RelationshipTypeManager> relationship_type_manager;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(RelationshipInstanceManager);

};

}
}

#endif /* SRC_ENGINE_ENTITY_RELATIONSHIPINSTANCEMANAGER_H_ */
