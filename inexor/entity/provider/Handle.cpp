/*
 * Handle.cpp
 *
 *  Created on: 15.02.2015
 *      Author: aschaeffer
 */

#include "Handle.hpp"

namespace inexor {
namespace entity {

    HandleEntityTypeProvider::HandleEntityTypeProvider() : EntityTypeProvider(ENT_HANDLE)
    {
        entity_type = new EntityType(ENT_HANDLE, true, true);
    }

    HandleEntityTypeProvider::~HandleEntityTypeProvider()
    {
    }

    HandleRendererEntityTypeProvider::HandleRendererEntityTypeProvider() : EntityTypeProvider(ENT_HANDLE_RENDERER)
    {
        entity_type = new EntityType(ENT_HANDLE_RENDERER, true, true);
    }

    HandleRendererEntityTypeProvider::~HandleRendererEntityTypeProvider()
    {
    }

    HandlesRelationshipTypeProvider::HandlesRelationshipTypeProvider(std::shared_ptr<EntityTypeManager> entity_type_manager)
        : RelationshipTypeProvider(REL_HANDLES, entity_type_manager)
    {
        // Define the relationship type
        relationship_type = new RelationshipType(REL_HANDLES,
                                                 true,
                                                 true,
                                                 entity_type_manager->Get(ENT_HANDLE),
                                                 NULL);
    }

    HandlesRelationshipTypeProvider::~HandlesRelationshipTypeProvider()
    {
    }

    RendersHandleRelationshipTypeProvider::RendersHandleRelationshipTypeProvider(std::shared_ptr<EntityTypeManager> entity_type_manager)
        : RelationshipTypeProvider(REL_RENDERS_HANDLE, entity_type_manager)
    {
        // Define the relationship type
        relationship_type = new RelationshipType(REL_RENDERS_HANDLE,
                                                 true,
                                                 true,
                                                 entity_type_manager->Get(ENT_HANDLE_RENDERER),
		                                         entity_type_manager->Get(ENT_HANDLE));
    }

    RendersHandleRelationshipTypeProvider::~RendersHandleRelationshipTypeProvider()
    {
    }

}
}
