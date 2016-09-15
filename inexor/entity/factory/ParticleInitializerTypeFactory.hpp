/*
 * ParticleInitializerTypeFactory.h
 *
 *  Created on: 27.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_FACTORY_PARTICLEINITIALIZERTYPEFACTORY_H_
#define SRC_ENGINE_ENTITY_FACTORY_PARTICLEINITIALIZERTYPEFACTORY_H_

#include "EntityTypeFactory.hpp"
#include "../subsystem/particle/ParticleModel.hpp"
#include "../domain/TypeRefPtr.hpp"
#include "../domain/graph/EntityFunction.hpp"
#include "../domain/graph/EntityType.hpp"
#include "../domain/graph/RelationshipType.hpp"
#include "../manager/EntityTypeManager.hpp"
#include "../manager/RelationshipTypeManager.hpp"

namespace inexor {
namespace entity {
namespace particle {

    class ParticleInitializerTypeFactory : public EntityTypeFactory
    {
        public:

            ParticleInitializerTypeFactory(CefRefPtr<EntityTypeManager> entity_type_manager);
            virtual ~ParticleInitializerTypeFactory();

            TypeRefPtr<EntityType> Create(std::string name_suffix);
            TypeRefPtr<EntityType> Create(std::string name_suffix, FunctionRefPtr function);

        private:

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(ParticleInitializerTypeFactory);
    };

}
}
}

#endif /* SRC_ENGINE_ENTITY_FACTORY_PARTICLEINITIALIZERTYPEFACTORY_H_ */
