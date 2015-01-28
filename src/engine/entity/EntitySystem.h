/*
 * EntitySystem.h
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYSYSTEM_H_
#define SRC_ENGINE_ENTITY_ENTITYSYSTEM_H_

#include <typeinfo>

#include "EntitySystemBase.h"
#include "domain/InstanceBase.h"
#include "domain/TypeBase.h"
#include "domain/graph/EntityInstance.h"
#include "domain/graph/EntityType.h"
#include "domain/graph/RelationshipType.h"
#include "domain/graph/RelationshipInstance.h"
#include "manager/EntityInstanceManager.h"
#include "manager/EntityTypeManager.h"
#include "manager/RelationshipInstanceManager.h"
#include "manager/RelationshipTypeManager.h"
#include "subsystem/TeleportSubsystem.h"
#include "subsystem/ParticleSubsystem.h"

struct type_info_less
{
    bool operator() (const std::type_info* lhs, const std::type_info* rhs) const
    {
        return lhs->before(*rhs) != 0;
    }
};

class TypeMap
{
    typedef std::map<std::type_info const*, void *, type_info_less> TypenameToObject;
    TypenameToObject ObjectMap;

    public:
        template <typename T>
        T *Get () const
        {
            TypenameToObject::const_iterator iType = ObjectMap.find(&typeid(T));
            if (iType == ObjectMap.end())
                return NULL;
            return reinterpret_cast<T *>(iType->second);
        }
        template <typename T>
        void Set(T *value)
        {
            ObjectMap[&typeid(T)] = reinterpret_cast<void *>(value);
        }
};

class EntitySystem
{
    public:
        EntitySystem();
        virtual ~EntitySystem() {};

        CefRefPtr<EntityTypeManager> GetEntityTypeManager() { return entity_type_manager; };
        CefRefPtr<RelationshipTypeManager> GetRelationshipTypeManager() { return relationship_type_manager; };
        CefRefPtr<EntityInstanceManager> GetEntityInstanceManager() { return entity_instance_manager; };
        CefRefPtr<RelationshipInstanceManager> GetRelationshipInstanceManager() { return relationship_instance_manager; };

        template <typename T>
        T *GetSubsystem () const
        {
            return subsystems.Get<T>();
        }

        void SubsystemTest();
        void AttributeTest();
        void InstanceCreationTest();
        void TypeCreationTest();
        void LowLevelTypeCreationTest();
        void ParticleSystemTest();

        void Save(std::string filename);

        void Load(std::string filename);

    private:

        /**
         * The entity type manager.
         */
        CefRefPtr<EntityTypeManager> entity_type_manager;

        /**
         * The relationship type manager.
         */
        CefRefPtr<RelationshipTypeManager> relationship_type_manager;

        /**
         * The entity instance manager.
         */
        CefRefPtr<EntityInstanceManager> entity_instance_manager;

        /**
         * The relationship instance manager.
         */
        CefRefPtr<RelationshipInstanceManager> relationship_instance_manager;

        /**
         * The subsystems.
         */
        TypeMap subsystems;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntitySystem);
};

#endif /* SRC_ENGINE_ENTITY_ENTITYSYSTEM_H_ */
