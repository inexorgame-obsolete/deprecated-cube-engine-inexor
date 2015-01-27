/*
 * ParticleModifierTypeFactory.h
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_FACTORY_PARTICLEMODIFIERTYPEFACTORY_H_
#define SRC_ENGINE_ENTITY_FACTORY_PARTICLEMODIFIERTYPEFACTORY_H_

#include "EntityTypeFactory.h"
#include "../domain/graph/EntityFunction.h"
#include "../domain/graph/EntityType.h"
#include "../domain/graph/RelationshipType.h"
#include "../manager/EntityTypeManager.h"
#include "../manager/RelationshipTypeManager.h"

#define PARTICLE_MODIFIER_TYPE_FACTORY "particle_modifier_type_factory"
#define ENTTYPE_PREFIX_PARTICLE_MODIFIER_TYPE "particle_modifier_type_"

class ParticleModifierTypeFactory : public EntityTypeFactory
{
    public:
        ParticleModifierTypeFactory(CefRefPtr<EntityTypeManager> entity_type_manager) : EntityTypeFactory(PARTICLE_MODIFIER_TYPE_FACTORY, ENTTYPE_PREFIX_PARTICLE_MODIFIER_TYPE, entity_type_manager) {};
        virtual ~ParticleModifierTypeFactory() {};

        TypeRefPtr<EntityType> Create(std::string name_suffix);

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(ParticleModifierTypeFactory);
};

#endif /* SRC_ENGINE_ENTITY_FACTORY_PARTICLEMODIFIERTYPEFACTORY_H_ */
