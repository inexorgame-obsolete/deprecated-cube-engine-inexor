/*
 * RelationshipTypeManager.h
 *
 *  Created on: 24.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_RELATIONSHIPTYPEMANAGER_H_
#define SRC_ENGINE_ENTITY_RELATIONSHIPTYPEMANAGER_H_

#include "../EntitySystemBase.h"
#include "../domain/TypeRefPtr.h"
#include "../domain/graph/RelationshipType.h"

namespace inexor {
namespace entity {

class RelationshipTypeProvider;
class EntityTypeManager;

class RelationshipTypeManager
{
    public:
        RelationshipTypeManager(CefRefPtr<EntityTypeManager> entity_type_manager);
        virtual ~RelationshipTypeManager();

        TypeRefPtr<RelationshipType> Create(std::string name, TypeRefPtr<EntityType> startNodeType, TypeRefPtr<EntityType> endNodeType);
        TypeRefPtr<RelationshipType> Create(std::string name, std::string startNodeTypeName, std::string endNodeTypeName);
        TypeRefPtr<RelationshipType> Create(std::string name, bool persist, bool synchronize, TypeRefPtr<EntityType> startNodeType, TypeRefPtr<EntityType> endNodeType);
        TypeRefPtr<RelationshipType> Create(std::string name, bool persist, bool synchronize, std::string startNodeTypeName, std::string endNodeTypeName);

        void RegisterType(std::string relationship_type_name, TypeRefPtr<RelationshipType> relationship_type);
        void RegisterProvider(CefRefPtr<RelationshipTypeProvider> relationship_type_provider);

        TypeRefPtr<RelationshipType> Get(std::string relationship_type_name);
        bool Exists(std::string relationship_type_name);

        int Size();

    private:
        std::map<std::string, TypeRefPtr<RelationshipType> > relationship_types;

        // The entity type manager.
        CefRefPtr<EntityTypeManager> entity_type_manager;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(RelationshipTypeManager);
};

}
}

#endif /* SRC_ENGINE_ENTITY_RELATIONSHIPTYPEMANAGER_H_ */
