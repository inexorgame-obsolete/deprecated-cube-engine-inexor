/*
 * ParticleTypeFactory.h
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_FACTORY_PARTICLETYPEFACTORY_H_
#define SRC_ENGINE_ENTITY_FACTORY_PARTICLETYPEFACTORY_H_

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

class ParticleTypeFactory : public EntityTypeFactory
{
    public:
        ParticleTypeFactory(CefRefPtr<EntityTypeManager> entity_type_manager);
        virtual ~ParticleTypeFactory();

        TypeRefPtr<EntityType> Create(std::string name_suffix);
        TypeRefPtr<EntityType> Create(std::string name_suffix, std::string renderer_instance_name);

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(ParticleTypeFactory);
};

}
}
}

#endif /* SRC_ENGINE_ENTITY_FACTORY_PARTICLETYPEFACTORY_H_ */
