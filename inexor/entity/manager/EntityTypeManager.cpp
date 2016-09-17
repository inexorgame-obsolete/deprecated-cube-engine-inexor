/*
 * EntityTypeManager.cpp
 *
 *  Created on: 24.01.2015
 *      Author: aschaeffer
 */

#include "EntityTypeManager.hpp"
#include "../provider/EntityTypeProvider.hpp"
#include "../factory/EntityTypeFactory.hpp"

namespace inexor {
namespace entity {

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
        entity_type_uuids[entity_type->uuid] = entity_type_name;
        return entity_type;
    }

    TypeRefPtr<EntityType> EntityTypeManager::Create(std::string entity_type_name, bool persist, bool synchronize, TypeRefPtr<EntityType> parent_type)
    {
        TypeRefPtr<EntityType> entity_type = new EntityType(entity_type_name, persist, synchronize, parent_type);
        entity_types[entity_type_name] = entity_type;
        entity_type_uuids[entity_type->uuid] = entity_type_name;
        return entity_type;
    }

    TypeRefPtr<EntityType> EntityTypeManager::Create(std::string factory_name, std::string entity_type_name_suffix)
    {
        return entity_type_factories[factory_name]->Create(entity_type_name_suffix);
    }

    void EntityTypeManager::RegisterType(std::string entity_type_name, TypeRefPtr<EntityType> entity_type)
    {
        entity_types[entity_type_name] = entity_type;
        entity_type_uuids[entity_type->uuid] = entity_type->uuid;
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

    TypeRefPtr<EntityType> EntityTypeManager::GetByUuid(std::string entity_type_uuid)
    {
        return Get(entity_type_uuids[entity_type_uuid]);
    }

    bool EntityTypeManager::Exists(std::string entity_type_name)
    {
        return entity_types.count(entity_type_name);
    }

    void EntityTypeManager::DeleteType(TypeRefPtr<EntityType> entity_type)
    {
        entity_type_uuids.erase(entity_type->uuid);
        entity_types.erase(entity_type->name);
    }

    void EntityTypeManager::DeleteTypeByName(std::string entity_type_name)
    {
        DeleteType(Get(entity_type_name));
    }

    void EntityTypeManager::DeleteTypeByUuid(std::string entity_type_uuid)
    {
        DeleteType(GetByUuid(entity_type_uuid));
    }

    void EntityTypeManager::DeleteAllTypes()
    {
        entity_type_uuids.clear();
        entity_types.clear();
    }

    int EntityTypeManager::Size() {
        return entity_types.size();
    }

}
}
