/*
 * Handle.hpp
 *
 *  Created on: 18.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_PROVIDER_HANDLE_H_
#define SRC_ENGINE_ENTITY_PROVIDER_HANDLE_H_

#include "EntityTypeProvider.hpp"
#include "RelationshipTypeProvider.hpp"
#include "../domain/graph/EntityFunction.hpp"
#include "../domain/graph/EntityType.hpp"
#include "../domain/graph/RelationshipType.hpp"

namespace inexor {
namespace entity {

    /**
     *
     */
    class HandleEntityTypeProvider : public EntityTypeProvider
    {
        public:

            HandleEntityTypeProvider();
            virtual ~HandleEntityTypeProvider();

        private:

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(HandleEntityTypeProvider);

    };

    /**
     *
     */
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

            HandlesRelationshipTypeProvider(std::shared_ptr<EntityTypeManager> entity_type_manager);
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

            RendersHandleRelationshipTypeProvider(std::shared_ptr<EntityTypeManager> entity_type_manager);
            virtual ~RendersHandleRelationshipTypeProvider();

        private:

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(RendersHandleRelationshipTypeProvider);

    };

}
}

#endif /* SRC_ENGINE_ENTITY_PROVIDER_HANDLE_H_ */
