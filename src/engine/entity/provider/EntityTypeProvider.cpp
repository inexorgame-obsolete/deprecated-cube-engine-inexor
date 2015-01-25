/*
 * EntityTypeProvider.cpp
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#include "EntityTypeProvider.h"
#include "../manager/EntityTypeManager.h"

EntityTypeProvider::EntityTypeProvider(
    std::string entity_name,
    CefRefPtr<EntityTypeManager> entity_type_manager
) : entity_name(entity_name),
    entity_type_manager(entity_type_manager) {}
