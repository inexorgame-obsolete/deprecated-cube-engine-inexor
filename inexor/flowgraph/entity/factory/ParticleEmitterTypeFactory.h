/*
 * ParticleProvider.h
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_FACTORY_PARTICLEEMITTERTYPEFACTORY_H_
#define SRC_ENGINE_ENTITY_FACTORY_PARTICLEEMITTERTYPEFACTORY_H_

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

class ParticleEmitterTypeFactory : public EntityTypeFactory
{
    public:
        ParticleEmitterTypeFactory(CefRefPtr<EntityTypeManager> entity_type_manager);
        virtual ~ParticleEmitterTypeFactory();

        TypeRefPtr<EntityType> Create(std::string name_suffix);
        TypeRefPtr<EntityType> Create(std::string name_suffix, FunctionRefPtr function, std::string particle_type_name, int rate, int batch_size, int lifetime, double mass, double density);

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(ParticleEmitterTypeFactory);
};

}
}
}

#endif /* SRC_ENGINE_ENTITY_FACTORY_PARTICLEEMITTERTYPEFACTORY_H_ */
