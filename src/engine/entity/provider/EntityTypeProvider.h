/*
 * EntityTypeProvider.h
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_PROVIDER_ENTITYTYPEPROVIDER_H_
#define SRC_ENGINE_ENTITY_PROVIDER_ENTITYTYPEPROVIDER_H_

#include "../domain/TypeBase.h"
#include "../domain/TypeRefPtr.h"

namespace inexor {
namespace entity {

class EntityTypeProvider
{
    public:
        EntityTypeProvider(std::string entity_name);
        virtual ~EntityTypeProvider();

        std::string GetEntityName();
        TypeRefPtr<EntityType> GetEntityType();

    protected:
        TypeRefPtr<EntityType> entity_type;
        std::string entity_name;

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityTypeProvider);
};

}
}

#endif /* SRC_ENGINE_ENTITY_PROVIDER_ENTITYTYPEPROVIDER_H_ */
