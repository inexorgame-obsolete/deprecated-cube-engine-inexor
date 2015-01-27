/*
 * ParticleTypeFactory.h
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_FACTORY_PARTICLETYPEFACTORY_H_
#define SRC_ENGINE_ENTITY_FACTORY_PARTICLETYPEFACTORY_H_

#include "EntityTypeFactory.h"
#include "../domain/graph/EntityFunction.h"
#include "../domain/graph/EntityType.h"
#include "../domain/graph/RelationshipType.h"
#include "../manager/EntityTypeManager.h"
#include "../manager/RelationshipTypeManager.h"

#define PARTICLE_TYPE_FACTORY "particle_type_factory"
#define ENTTYPE_PREFIX_PARTICLE_TYPE "particle_type_"

class ParticleTypeFactory : public EntityTypeFactory
{
    public:
        ParticleTypeFactory(CefRefPtr<EntityTypeManager> entity_type_manager);
        virtual ~ParticleTypeFactory();

        TypeRefPtr<EntityType> Create(std::string name_suffix);

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(ParticleTypeFactory);
};

#endif /* SRC_ENGINE_ENTITY_FACTORY_PARTICLETYPEFACTORY_H_ */
