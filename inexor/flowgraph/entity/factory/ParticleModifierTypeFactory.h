/*
 * ParticleModifierTypeFactory.h
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_FACTORY_PARTICLEMODIFIERTYPEFACTORY_H_
#define SRC_ENGINE_ENTITY_FACTORY_PARTICLEMODIFIERTYPEFACTORY_H_

#include "EntityTypeFactory.h"
#include "../subsystem/particle/ParticleModel.h"
#include "../domain/TypeRefPtr.h"
#include "../domain/graph/EntityFunction.h"
#include "../domain/graph/EntityType.h"
#include "../domain/graph/RelationshipType.h"
#include "../manager/EntityTypeManager.h"
#include "../manager/RelationshipTypeManager.h"

namespace inexor {
namespace entity {
namespace particle {

class ParticleModifierTypeFactory : public EntityTypeFactory
{
    public:
        ParticleModifierTypeFactory(CefRefPtr<EntityTypeManager> entity_type_manager);
        virtual ~ParticleModifierTypeFactory();

        TypeRefPtr<EntityType> Create(std::string name_suffix);
        TypeRefPtr<EntityType> Create(std::string name_suffix, FunctionRefPtr function);

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(ParticleModifierTypeFactory);
};

}
}
}

#endif /* SRC_ENGINE_ENTITY_FACTORY_PARTICLEMODIFIERTYPEFACTORY_H_ */
