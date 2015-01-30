/*
 * ParticleProvider.h
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_FACTORY_PARTICLEEMITTERTYPEFACTORY_H_
#define SRC_ENGINE_ENTITY_FACTORY_PARTICLEEMITTERTYPEFACTORY_H_

#include "EntityTypeFactory.h"
#include "../domain/TypeRefPtr.h"
#include "../domain/graph/EntityFunction.h"
#include "../domain/graph/EntityType.h"
#include "../domain/graph/RelationshipType.h"
#include "../manager/EntityTypeManager.h"
#include "../manager/RelationshipTypeManager.h"
#include "../provider/ParticleProvider.h"

#define PARTICLE_EMITTER_TYPE_FACTORY "particle_emitter_type_factory"
#define ENTTYPE_PREFIX_PARTICLE_EMITTER_TYPE "particle_emitter_type_"

class ParticleEmitterTypeFactory : public EntityTypeFactory
{
    public:
        ParticleEmitterTypeFactory(CefRefPtr<EntityTypeManager> entity_type_manager) : EntityTypeFactory(PARTICLE_EMITTER_TYPE_FACTORY, ENTTYPE_PREFIX_PARTICLE_EMITTER_TYPE, entity_type_manager) {};
        virtual ~ParticleEmitterTypeFactory() {};

        TypeRefPtr<EntityType> Create(std::string name_suffix);

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(ParticleEmitterTypeFactory);
};

#endif /* SRC_ENGINE_ENTITY_FACTORY_PARTICLEEMITTERTYPEFACTORY_H_ */
