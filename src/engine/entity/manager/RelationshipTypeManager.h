/*
 * RelationshipTypeManager.h
 *
 *  Created on: 24.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_RELATIONSHIPTYPEMANAGER_H_
#define SRC_ENGINE_ENTITY_RELATIONSHIPTYPEMANAGER_H_

#include "../EntitySystemBase.h"
#include "../RelationshipType.h"

class RelationshipTypeProvider;

class RelationshipTypeManager
{
    public:
        RelationshipTypeManager() {};
        virtual ~RelationshipTypeManager() {};

        TypeRefPtr<RelationshipType> Create(std::string name, TypeRefPtr<EntityType> startNodeType, TypeRefPtr<EntityType> endNodeType);
        TypeRefPtr<RelationshipType> Create(std::string name, bool persist, bool synchronize, TypeRefPtr<EntityType> startNodeType, TypeRefPtr<EntityType> endNodeType);

        void RegisterType(std::string relationship_type_name, TypeRefPtr<RelationshipType> relationship_type);
        void RegisterProvider(CefRefPtr<RelationshipTypeProvider> relationship_type_provider);

        TypeRefPtr<RelationshipType> Get(std::string relationship_type_name);
        bool Exists(std::string relationship_type_name);

        int Size();

    private:
        std::map<std::string, TypeRefPtr<RelationshipType> > relationship_types;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(RelationshipTypeManager);
};

#endif /* SRC_ENGINE_ENTITY_RELATIONSHIPTYPEMANAGER_H_ */
