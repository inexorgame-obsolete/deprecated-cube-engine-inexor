/*
 * EntityTypeProvider.cpp
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#include "EntityTypeFactory.h"
#include "../manager/EntityTypeManager.h"

namespace inexor {
namespace entity {

EntityTypeFactory::EntityTypeFactory(
    std::string factory_name,
    std::string function_attribute_name,
    std::string entity_name_prefix,
    CefRefPtr<EntityTypeManager> entity_type_manager
) : factory_name(factory_name),
    function_attribute_name(function_attribute_name),
    entity_type_name_prefix(entity_name_prefix),
    entity_type_manager(entity_type_manager)
{
}

EntityTypeFactory::~EntityTypeFactory()
{
}

std::string EntityTypeFactory::GetFactoryName()
{
    return factory_name;
}

std::string EntityTypeFactory::GetFunctionAttributeName()
{
    return function_attribute_name;
}

std::string EntityTypeFactory::GetEntityTypeNamePrefix()
{
    return entity_type_name_prefix;
}

TypeRefPtr<EntityType> EntityTypeFactory::Create(std::string name_suffix)
{
    std::string entity_type_name = entity_type_name_prefix + name_suffix;
    TypeRefPtr<EntityType> entity_type = entity_type_manager->Create(name_suffix, false, false);
    return entity_type;
}

}
}
