/*
 * RelationshipTypeManager.h
 *
 *  Created on: 24.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_RELATIONSHIPTYPEMANAGER_H_
#define SRC_ENGINE_ENTITY_RELATIONSHIPTYPEMANAGER_H_

#include "../EntitySystemBase.hpp"
#include "../domain/TypeRefPtr.hpp"
#include "../domain/graph/RelationshipType.hpp"

namespace inexor {
namespace entity {

    class RelationshipTypeProvider;
    class EntityTypeManager;

    class RelationshipTypeManager
    {
        public:

            RelationshipTypeManager(std::shared_ptr<EntityTypeManager> entity_type_manager);
            virtual ~RelationshipTypeManager();

            TypeRefPtr<RelationshipType> Create(std::string name, TypeRefPtr<EntityType> startNodeType, TypeRefPtr<EntityType> endNodeType);
            TypeRefPtr<RelationshipType> Create(std::string name, std::string startNodeTypeName, std::string endNodeTypeName);
            TypeRefPtr<RelationshipType> Create(std::string name, bool persist, bool synchronize, TypeRefPtr<EntityType> startNodeType, TypeRefPtr<EntityType> endNodeType);
            TypeRefPtr<RelationshipType> Create(std::string name, bool persist, bool synchronize, std::string startNodeTypeName, std::string endNodeTypeName);

            void RegisterType(std::string relationship_type_name, TypeRefPtr<RelationshipType> relationship_type);
            void RegisterProvider(std::shared_ptr<RelationshipTypeProvider> relationship_type_provider);

            TypeRefPtr<RelationshipType> Get(std::string relationship_type_name);
            TypeRefPtr<RelationshipType> GetByUuid(std::string relationship_type_uuid);
            bool Exists(std::string relationship_type_name);

            void DeleteType(TypeRefPtr<RelationshipType> relationship_type);
            void DeleteTypeByName(std::string relationship_type_name);
            void DeleteTypeByUuid(std::string relationship_type_uuid);
            void DeleteAllTypes();

            int Size();

        private:

            /**
             * The key is the NAME of the relationship type.
             */
            std::unordered_map<std::string, TypeRefPtr<RelationshipType> > relationship_types;

            /**
             * The key is the UUID, the value is the NAME of the relationship type.
             */
            std::unordered_map<std::string, std::string> relationship_type_uuids;

            // The entity type manager.
            std::shared_ptr<EntityTypeManager> entity_type_manager;

    };

}
}

#endif /* SRC_ENGINE_ENTITY_RELATIONSHIPTYPEMANAGER_H_ */
