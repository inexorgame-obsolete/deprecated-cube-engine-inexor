/*
 * RelationshipTypeProvider.cpp
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#include "RelationshipTypeProvider.h"
#include "../manager/RelationshipTypeManager.h"

RelationshipTypeProvider::RelationshipTypeProvider(
    std::string relationship_name,
    CefRefPtr<RelationshipTypeManager> relationship_type_manager,
    CefRefPtr<EntityTypeManager> entity_type_manager
) : relationship_name(relationship_name),
    relationship_type_manager(relationship_type_manager),
    entity_type_manager(entity_type_manager) {};
