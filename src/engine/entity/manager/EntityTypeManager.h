/*
 * EntityTypeManager.h
 *
 *  Created on: 24.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYTYPEMANAGER_H_
#define SRC_ENGINE_ENTITY_ENTITYTYPEMANAGER_H_

#include "../EntitySystemBase.h"
#include "../EntityType.h"

class EntityTypeProvider;

class EntityTypeManager
{
    public:
        EntityTypeManager() {};
        virtual ~EntityTypeManager() {};

        TypeRefPtr<EntityType> Create(std::string name, bool persist, bool synchronize);

        void Register(std::string entity_type_name, TypeRefPtr<EntityType> entity_type);
        void Register(CefRefPtr<EntityTypeProvider> entity_type_provider);

        TypeRefPtr<EntityType> Get(std::string entity_type_name);
        bool Exists(std::string entity_type_name);

        int Size();

    private:
        std::map<std::string, TypeRefPtr<EntityType> > entity_types;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityTypeManager);

};

#endif /* SRC_ENGINE_ENTITY_ENTITYTYPEMANAGER_H_ */
