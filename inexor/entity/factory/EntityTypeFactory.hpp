/*
 * EntityTypeProvider.h
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_FACTORY_ENTITYTYPEFACTORY_H_
#define SRC_ENGINE_ENTITY_FACTORY_ENTITYTYPEFACTORY_H_

#include "../domain/TypeBase.hpp"
#include "../domain/TypeRefPtr.hpp"

namespace inexor {
namespace entity {

class EntityTypeManager;

class EntityTypeFactory
{
    public:
        EntityTypeFactory(std::string factory_name, std::string function_attribute_name, std::string entity_name_prefix, CefRefPtr<EntityTypeManager> entity_type_manager);
        virtual ~EntityTypeFactory();

        /**
         * Returns the name of the factory.
         */
        std::string GetFactoryName();

        /**
         * Returns the attribute name for the function.
         */
        std::string GetFunctionAttributeName();

        /**
         * Returns the entity type name prefix.
         */
        std::string GetEntityTypeNamePrefix();

        TypeRefPtr<EntityType> Create(std::string name_suffix);

    protected:
        std::string factory_name;
        std::string function_attribute_name;
        std::string entity_type_name_prefix;
        CefRefPtr<EntityTypeManager> entity_type_manager;

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityTypeFactory);
};

}
}

#endif /* SRC_ENGINE_ENTITY_FACTORY_ENTITYTYPEFACTORY_H_ */
