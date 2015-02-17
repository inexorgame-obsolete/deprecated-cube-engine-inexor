/*
 * Handle.h
 *
 *  Created on: 18.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_PROVIDER_HANDLE_H_
#define SRC_ENGINE_ENTITY_PROVIDER_HANDLE_H_

#include "EntityTypeProvider.h"
#include "RelationshipTypeProvider.h"
#include "../domain/graph/EntityFunction.h"
#include "../domain/graph/EntityType.h"
#include "../domain/graph/RelationshipType.h"

namespace inexor {
namespace entity {

class HandleEntityTypeProvider : public EntityTypeProvider
{
    public:
        HandleEntityTypeProvider();
        virtual ~HandleEntityTypeProvider();

    private:

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(HandleEntityTypeProvider);

};

class HandleRendererEntityTypeProvider : public EntityTypeProvider
{
    public:
        HandleRendererEntityTypeProvider();
        virtual ~HandleRendererEntityTypeProvider();

    private:

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(HandleRendererEntityTypeProvider);

};

/**
 * Defines a relationship between a handle and any other entity instance with a position.
 */
class HandlesRelationshipTypeProvider : public RelationshipTypeProvider
{
    public:
        HandlesRelationshipTypeProvider(CefRefPtr<EntityTypeManager> entity_type_manager);
        virtual ~HandlesRelationshipTypeProvider();

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(HandlesRelationshipTypeProvider);

};

/**
 * Defines a relationship between a handle renderer and a handle.
 */
class RendersHandleRelationshipTypeProvider : public RelationshipTypeProvider
{
    public:
        RendersHandleRelationshipTypeProvider(CefRefPtr<EntityTypeManager> entity_type_manager);
        virtual ~RendersHandleRelationshipTypeProvider();

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(RendersHandleRelationshipTypeProvider);

};

}
}

#endif /* SRC_ENGINE_ENTITY_PROVIDER_HANDLE_H_ */
