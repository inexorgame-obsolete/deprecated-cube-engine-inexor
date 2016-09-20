/*
 * RelationshipTypeManager.cpp
 *
 *  Created on: 24.01.2015
 *      Author: aschaeffer
 */

#include "RelationshipTypeManager.hpp"
#include "../provider/RelationshipTypeProvider.hpp"
#include "../manager/EntityTypeManager.hpp"

namespace inexor {
namespace entity {

    RelationshipTypeManager::RelationshipTypeManager(std::shared_ptr<EntityTypeManager> entity_type_manager) : entity_type_manager(entity_type_manager)
    {
    }

    RelationshipTypeManager::~RelationshipTypeManager()
    {
    }

    TypeRefPtr<RelationshipType> RelationshipTypeManager::Create(std::string name, TypeRefPtr<EntityType> startNodeTypeName, TypeRefPtr<EntityType> endNodeTypeName)
    {
        // Create an relationship type that won't be persisted/synchronized
        return Create(name, false, false, startNodeTypeName, endNodeTypeName);
    }

    TypeRefPtr<RelationshipType> RelationshipTypeManager::Create(std::string name, std::string startNodeType, std::string endNodeType)
    {
        // Create an relationship type that won't be persisted/synchronized
        return Create(name, false, false, startNodeType, endNodeType);
    }

    TypeRefPtr<RelationshipType> RelationshipTypeManager::Create(std::string name, bool persist, bool synchronize, TypeRefPtr<EntityType> startNodeType, TypeRefPtr<EntityType> endNodeType)
    {
        TypeRefPtr<RelationshipType> relationship_type = std::make_shared<RelationshipType>(name, persist, synchronize, startNodeType, endNodeType);
        relationship_types[name] = relationship_type;
        relationship_type_uuids[relationship_type->uuid] = name;
        return relationship_type;
    }

    TypeRefPtr<RelationshipType> RelationshipTypeManager::Create(std::string name, bool persist, bool synchronize, std::string startNodeTypeName, std::string endNodeTypeName)
    {
        TypeRefPtr<EntityType> startNodeType = entity_type_manager->Get(startNodeTypeName);
        TypeRefPtr<EntityType> endNodeType = entity_type_manager->Get(endNodeTypeName);
        TypeRefPtr<RelationshipType> relationship_type = std::make_shared<RelationshipType>(name, persist, synchronize, startNodeType, endNodeType);
        relationship_types[name] = relationship_type;
        relationship_type_uuids[relationship_type->uuid] = name;
        return relationship_type;
    }

    void RelationshipTypeManager::RegisterType(std::string relationship_type_name, TypeRefPtr<RelationshipType> relationship_type) {
        relationship_types[relationship_type_name] = relationship_type;
        relationship_type_uuids[relationship_type->uuid] = relationship_type_name;
    };

    void RelationshipTypeManager::RegisterProvider(std::shared_ptr<RelationshipTypeProvider> relationship_type_provider) {
        RegisterType(relationship_type_provider->GetRelationshipName(), relationship_type_provider->GetRelationshipType());
    };

    TypeRefPtr<RelationshipType> RelationshipTypeManager::Get(std::string relationship_type_name) {
        return relationship_types[relationship_type_name];
    };

    TypeRefPtr<RelationshipType> RelationshipTypeManager::GetByUuid(std::string relationship_type_uuid) {
        return Get(relationship_type_uuids[relationship_type_uuid]);
    };

    bool RelationshipTypeManager::Exists(std::string relationship_type_name) {
        return relationship_types.count(relationship_type_name);
    };

    void RelationshipTypeManager::DeleteType(TypeRefPtr<RelationshipType> relationship_type)
    {
        relationship_type_uuids.erase(relationship_type->uuid);
        relationship_types.erase(relationship_type->name);
    }

    void RelationshipTypeManager::DeleteTypeByName(std::string relationship_type_name)
    {
        DeleteType(Get(relationship_type_name));
    }

    void RelationshipTypeManager::DeleteTypeByUuid(std::string relationship_type_uuid)
    {
        DeleteType(GetByUuid(relationship_type_uuid));
    }

    void RelationshipTypeManager::DeleteAllTypes()
    {
        relationship_type_uuids.clear();
        relationship_types.clear();
    }

    int RelationshipTypeManager::Size() {
        return relationship_types.size();
    }

}
}
