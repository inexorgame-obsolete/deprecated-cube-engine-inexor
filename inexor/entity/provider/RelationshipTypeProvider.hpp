/*
 * RelationshipTypeProvider.h
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_PROVIDER_RELATIONSHIPTYPEPROVIDER_H_
#define SRC_ENGINE_ENTITY_PROVIDER_RELATIONSHIPTYPEPROVIDER_H_

#include "../domain/TypeBase.hpp"
#include "../domain/graph/EntityType.hpp"
#include "../manager/EntityTypeManager.hpp"

namespace inexor {
namespace entity {

    class RelationshipTypeProvider
    {
        public:

            RelationshipTypeProvider(
                std::string relationship_name,
                std::shared_ptr<EntityTypeManager> entity_type_manager
            );
            virtual ~RelationshipTypeProvider() {};

            std::string GetRelationshipName() { return relationship_name; };
            TypeRefPtr<RelationshipType> GetRelationshipType() { return relationship_type; };

        protected:

            std::string relationship_name;
            std::shared_ptr<EntityTypeManager> entity_type_manager;
            TypeRefPtr<RelationshipType> relationship_type;

        private:
            
            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(RelationshipTypeProvider);
    };

}
}

#endif /* SRC_ENGINE_ENTITY_PROVIDER_RELATIONSHIPTYPEPROVIDER_H_ */
