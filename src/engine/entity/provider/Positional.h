/*
 * Positional.h
 *
 *  Created on: 18.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_PROVIDER_POSITIONAL_H_
#define SRC_ENGINE_ENTITY_PROVIDER_POSITIONAL_H_

#include "EntityTypeProvider.h"
#include "../domain/graph/EntityFunction.h"
#include "../domain/graph/EntityType.h"
#include "../domain/graph/RelationshipType.h"

class PositionalEntityTypeProvider : public EntityTypeProvider
{
    public:
        PositionalEntityTypeProvider(std::string entity_type_name) : EntityTypeProvider(entity_type_name) {};
        virtual ~PositionalEntityTypeProvider() {};

    private:

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(PositionalEntityTypeProvider);

};

#endif /* SRC_ENGINE_ENTITY_PROVIDER_POSITIONAL_H_ */
