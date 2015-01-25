/*
 * RelationshipTypeProvider.h
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_PROVIDER_RELATIONSHIPTYPEPROVIDER_H_
#define SRC_ENGINE_ENTITY_PROVIDER_RELATIONSHIPTYPEPROVIDER_H_

#include "../TypeBase.h"
#include "../EntityType.h"

class RelationshipTypeManager;

class RelationshipTypeProvider
{
    public:
        RelationshipTypeProvider(
            std::string relationship_name,
            CefRefPtr<RelationshipTypeManager> relationship_type_manager,
            CefRefPtr<EntityTypeManager> entity_type_manager
        );
        virtual ~RelationshipTypeProvider() {};

        std::string GetRelationshipName() { return relationship_name; };
        TypeRefPtr<RelationshipType> GetRelationshipType() { return relationship_type; };

    protected:
        CefRefPtr<RelationshipTypeManager> relationship_type_manager;
        CefRefPtr<EntityTypeManager> entity_type_manager;
        TypeRefPtr<RelationshipType> relationship_type;
        std::string relationship_name;

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(RelationshipTypeProvider);
};

#endif /* SRC_ENGINE_ENTITY_PROVIDER_RELATIONSHIPTYPEPROVIDER_H_ */
