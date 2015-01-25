/*
 * EntityTypeManager.cpp
 *
 *  Created on: 24.01.2015
 *      Author: aschaeffer
 */

#include "EntityTypeManager.h"
#include "../provider/EntityTypeProvider.h"

TypeRefPtr<EntityType> EntityTypeManager::Create(std::string name, bool persist, bool synchronize)
{
    TypeRefPtr<EntityType> entity_type = new EntityType(name, persist, synchronize);
    entity_types[name] = entity_type;
    return entity_type;
};

void EntityTypeManager::Register(std::string entity_type_name, TypeRefPtr<EntityType> entity_type)
{
    entity_types[entity_type_name] = entity_type;
};

void EntityTypeManager::Register(CefRefPtr<EntityTypeProvider> entity_type_provider)
{
   Register(entity_type_provider->GetEntityName(), entity_type_provider->GetEntityType());
};

TypeRefPtr<EntityType> EntityTypeManager::Get(std::string entity_type_name)
{
    return entity_types[entity_type_name];
};

bool EntityTypeManager::Exists(std::string entity_type_name)
{
    return entity_types.count(entity_type_name);
};

int EntityTypeManager::Size() {
    return entity_types.size();
}
