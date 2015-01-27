/*
 * RelationshipInstanceManager.h
 *
 *  Created on: 24.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_RELATIONSHIPINSTANCEMANAGER_H_
#define SRC_ENGINE_ENTITY_RELATIONSHIPINSTANCEMANAGER_H_

#include "RelationshipTypeManager.h"
#include "../EntitySystemBase.h"
#include "../domain/graph/RelationshipInstance.h"
#include "../domain/graph/RelationshipType.h"

class RelationshipInstanceManager
{
    public:
        RelationshipInstanceManager(CefRefPtr<RelationshipTypeManager> relationship_type_manager) : relationship_type_manager(relationship_type_manager) {};
        virtual ~RelationshipInstanceManager() {};

        InstanceRefPtr<RelationshipInstance> CreateInstance(TypeRefPtr<RelationshipType> relationship_type, InstanceRefPtr<EntityInstance> start_node, InstanceRefPtr<EntityInstance> end_node);
        InstanceRefPtr<RelationshipInstance> CreateInstance(std::string relationship_type_name, InstanceRefPtr<EntityInstance> start_node, InstanceRefPtr<EntityInstance> end_node);

        bool Exists(std::string uuid);
        InstanceRefPtr<RelationshipInstance> Get(std::string uuid);
        std::list<InstanceRefPtr<RelationshipInstance> > GetAll(TypeRefPtr<RelationshipType> relationship_type);
        std::list<InstanceRefPtr<RelationshipInstance> > GetAll(std::string relationship_type_name);

        void DeleteInstance(InstanceRefPtr<RelationshipInstance> instance);
        void DeleteInstance(std::string uuid);

        void DeleteAllInstances();
        void DeleteAllInstances(TypeRefPtr<RelationshipType> relationship_type);

        int Size();

    private:
        // The relationship instances.
        std::map<std::string, InstanceRefPtr<RelationshipInstance> > relationship_instances;

        // The relationship type manager.
        CefRefPtr<RelationshipTypeManager> relationship_type_manager;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(RelationshipInstanceManager);

};

#endif /* SRC_ENGINE_ENTITY_RELATIONSHIPINSTANCEMANAGER_H_ */
