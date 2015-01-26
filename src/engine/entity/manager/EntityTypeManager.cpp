/*
 * EntityTypeManager.cpp
 *
 *  Created on: 24.01.2015
 *      Author: aschaeffer
 */

#include "EntityTypeManager.h"
#include "../provider/EntityTypeProvider.h"
#include "../factory/EntityTypeFactory.h"

EntityTypeManager::EntityTypeManager()
{
}

EntityTypeManager::~EntityTypeManager()
{
}

TypeRefPtr<EntityType> EntityTypeManager::Create(std::string entity_type_name, bool persist, bool synchronize)
{
    TypeRefPtr<EntityType> entity_type = new EntityType(entity_type_name, persist, synchronize);
    entity_types[entity_type_name] = entity_type;
    return entity_type;
}

TypeRefPtr<EntityType> EntityTypeManager::Create(std::string factory_name, std::string entity_type_name_suffix)
{
    return entity_type_factories[factory_name]->Create(entity_type_name_suffix);
}

void EntityTypeManager::RegisterType(std::string entity_type_name, TypeRefPtr<EntityType> entity_type)
{
    entity_types[entity_type_name] = entity_type;
}

void EntityTypeManager::RegisterProvider(CefRefPtr<EntityTypeProvider> entity_type_provider)
{
   RegisterType(entity_type_provider->GetEntityName(), entity_type_provider->GetEntityType());
}

void EntityTypeManager::RegisterFactory(CefRefPtr<EntityTypeFactory> entity_type_factory)
{
    entity_type_factories[entity_type_factory->GetFactoryName()] = entity_type_factory;
}

TypeRefPtr<EntityType> EntityTypeManager::Get(std::string entity_type_name)
{
    return entity_types[entity_type_name];
}

bool EntityTypeManager::Exists(std::string entity_type_name)
{
    return entity_types.count(entity_type_name);
}

int EntityTypeManager::Size() {
    return entity_types.size();
}
