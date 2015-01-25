/*
 * EntityTypeProvider.h
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_PROVIDER_ENTITYTYPEPROVIDER_H_
#define SRC_ENGINE_ENTITY_PROVIDER_ENTITYTYPEPROVIDER_H_

#include "../TypeBase.h"

class EntityTypeManager;

class EntityTypeProvider
{
    public:
        EntityTypeProvider(std::string entity_name, CefRefPtr<EntityTypeManager> entity_type_manager);
        virtual ~EntityTypeProvider() {};

        std::string GetEntityName() { return entity_name; };
        TypeRefPtr<EntityType> GetEntityType() { return entity_type; };

    protected:
        CefRefPtr<EntityTypeManager> entity_type_manager;
        TypeRefPtr<EntityType> entity_type;
        std::string entity_name;

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityTypeProvider);
};

#endif /* SRC_ENGINE_ENTITY_PROVIDER_ENTITYTYPEPROVIDER_H_ */
