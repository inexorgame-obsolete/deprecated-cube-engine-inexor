/*
 * EntityTypeProvider.hpp
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_PROVIDER_ENTITYTYPEPROVIDER_H_
#define SRC_ENGINE_ENTITY_PROVIDER_ENTITYTYPEPROVIDER_H_

#include "../domain/TypeBase.hpp"
#include "../domain/TypeRefPtr.hpp"

namespace inexor {
namespace entity {

    /**
     *
     */
    class EntityTypeProvider
    {
        public:

            EntityTypeProvider(std::string entity_name);
            virtual ~EntityTypeProvider();

            /**
             *
             */
            std::string GetEntityName();

            /**
             *
             */
            TypeRefPtr<EntityType> GetEntityType();

        protected:

            TypeRefPtr<EntityType> entity_type;
            std::string entity_name;

    };

}
}

#endif /* SRC_ENGINE_ENTITY_PROVIDER_ENTITYTYPEPROVIDER_H_ */
