/*
 * ParticleTypeFactory.h
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_FACTORY_PARTICLETYPEFACTORY_H_
#define SRC_ENGINE_ENTITY_FACTORY_PARTICLETYPEFACTORY_H_

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

    class ParticleTypeFactory : public EntityTypeFactory
    {
        public:

            ParticleTypeFactory(std::shared_ptr<EntityTypeManager> entity_type_manager);
            virtual ~ParticleTypeFactory();

            TypeRefPtr<EntityType> Create(std::string name_suffix);
            TypeRefPtr<EntityType> Create(std::string name_suffix, std::string renderer_instance_name);

    };

}
}
}

#endif /* SRC_ENGINE_ENTITY_FACTORY_PARTICLETYPEFACTORY_H_ */
