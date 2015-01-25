/*
 * Positional.h
 *
 *  Created on: 18.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_PROVIDER_POSITIONAL_H_
#define SRC_ENGINE_ENTITY_PROVIDER_POSITIONAL_H_

#include "../EntityFunction.h"
#include "../EntityType.h"
#include "../RelationshipType.h"
#include "EntityTypeProvider.h"

class PositionalEntityTypeProvider : public EntityTypeProvider
{
    public:
        PositionalEntityTypeProvider(
            std::string entity_type_name,
            CefRefPtr<EntityTypeManager> entity_type_manager
        ) : EntityTypeProvider(entity_type_name, entity_type_manager) {};
        virtual ~PositionalEntityTypeProvider() {};

    private:

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(PositionalEntityTypeProvider);

};

#endif /* SRC_ENGINE_ENTITY_PROVIDER_POSITIONAL_H_ */
