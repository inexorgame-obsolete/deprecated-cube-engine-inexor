/*
 * ParticleModifierTypeFactory.h
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_FACTORY_PARTICLEMODIFIERTYPEFACTORY_H_
#define SRC_ENGINE_ENTITY_FACTORY_PARTICLEMODIFIERTYPEFACTORY_H_

#include "inexor/entity/factory/EntityTypeFactory.hpp"
#include "inexor/entity/domain/TypeRefPtr.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityType.hpp"
#include "inexor/entity/domain/graph/RelationshipType.hpp"
#include "inexor/entity/manager/EntityTypeManager.hpp"
#include "inexor/entity/manager/RelationshipTypeManager.hpp"
#include "inexor/particle/model/ParticleModel.hpp"

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
