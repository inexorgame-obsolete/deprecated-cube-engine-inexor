/*
 * RelationshipTypeManager.cpp
 *
 *  Created on: 24.01.2015
 *      Author: aschaeffer
 */

#include "RelationshipTypeManager.h"
#include "../provider/RelationshipTypeProvider.h"

TypeRefPtr<RelationshipType> RelationshipTypeManager::Create(std::string name, TypeRefPtr<EntityType> startNodeType, TypeRefPtr<EntityType> endNodeType)
{
    // Create an relationship type that won't be persisted/synchronized
    return Create(name, false, false, startNodeType, endNodeType);
}

TypeRefPtr<RelationshipType> RelationshipTypeManager::Create(std::string name, bool persist, bool synchronize, TypeRefPtr<EntityType> startNodeType, TypeRefPtr<EntityType> endNodeType)
{
    TypeRefPtr<RelationshipType> relationship_type = new RelationshipType(name, persist, synchronize, startNodeType, endNodeType);
    relationship_types[name] = relationship_type;
    return relationship_type;
}

void RelationshipTypeManager::RegisterType(std::string relationship_type_name, TypeRefPtr<RelationshipType> relationship_type) {
    relationship_types[relationship_type_name] = relationship_type;
};

void RelationshipTypeManager::RegisterProvider(CefRefPtr<RelationshipTypeProvider> relationship_type_provider) {
    RegisterType(relationship_type_provider->GetRelationshipName(), relationship_type_provider->GetRelationshipType());
};

TypeRefPtr<RelationshipType> RelationshipTypeManager::Get(std::string relationship_type_name) {
    return relationship_types[relationship_type_name];
};

bool RelationshipTypeManager::Exists(std::string relationship_type_name) {
    return relationship_types.count(relationship_type_name);
};

int RelationshipTypeManager::Size() {
    return relationship_types.size();
}
