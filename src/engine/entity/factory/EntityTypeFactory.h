/*
 * EntityTypeProvider.h
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_FACTORY_ENTITYTYPEFACTORY_H_
#define SRC_ENGINE_ENTITY_FACTORY_ENTITYTYPEFACTORY_H_

#include "../TypeBase.h"

class EntityTypeManager;

class EntityTypeFactory
{
    public:
        EntityTypeFactory(std::string factory_name, std::string entity_name_prefix, CefRefPtr<EntityTypeManager> entity_type_manager);
        virtual ~EntityTypeFactory();

        std::string GetFactoryName();
        std::string GetEntityTypeNamePrefix();

        TypeRefPtr<EntityType> Create(std::string name_suffix);

    protected:
        std::string factory_name;
        std::string entity_type_name_prefix;
        CefRefPtr<EntityTypeManager> entity_type_manager;

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityTypeFactory);
};

#endif /* SRC_ENGINE_ENTITY_FACTORY_ENTITYTYPEFACTORY_H_ */
