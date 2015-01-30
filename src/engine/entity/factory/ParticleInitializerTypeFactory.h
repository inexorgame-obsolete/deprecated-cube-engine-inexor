/*
 * ParticleInitializerTypeFactory.h
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_FACTORY_PARTICLEINITIALIZERTYPEFACTORY_H_
#define SRC_ENGINE_ENTITY_FACTORY_PARTICLEINITIALIZERTYPEFACTORY_H_

#include "EntityTypeFactory.h"
#include "../domain/TypeRefPtr.h"
#include "../domain/graph/EntityFunction.h"
#include "../domain/graph/EntityType.h"
#include "../domain/graph/RelationshipType.h"
#include "../manager/EntityTypeManager.h"
#include "../manager/RelationshipTypeManager.h"
#include "../provider/ParticleProvider.h"

#define PARTICLE_INITIALIZER_TYPE_FACTORY "particle_initializer_type_factory"
#define ENTTYPE_PREFIX_PARTICLE_INITIALIZER_TYPE "particle_initializer_type_"

class ParticleInitializerTypeFactory : public EntityTypeFactory
{
    public:
        ParticleInitializerTypeFactory(CefRefPtr<EntityTypeManager> entity_type_manager) : EntityTypeFactory(PARTICLE_INITIALIZER_TYPE_FACTORY, ENTTYPE_PREFIX_PARTICLE_INITIALIZER_TYPE, entity_type_manager) {};
        virtual ~ParticleInitializerTypeFactory() {};

        TypeRefPtr<EntityType> Create(std::string name_suffix);

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(ParticleInitializerTypeFactory);
};

#endif /* SRC_ENGINE_ENTITY_FACTORY_PARTICLEINITIALIZERTYPEFACTORY_H_ */
