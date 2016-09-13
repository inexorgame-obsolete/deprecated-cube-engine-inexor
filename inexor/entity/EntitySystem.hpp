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
#include "domain/TimeStep.h"
#include "domain/TypeBase.h"
#include "domain/graph/EntityInstance.h"
#include "domain/graph/EntityType.h"
#include "domain/graph/RelationshipType.h"
#include "domain/graph/RelationshipInstance.h"
#include "manager/EntityInstanceManager.h"
#include "manager/EntityTypeManager.h"
#include "manager/RelationshipInstanceManager.h"
#include "manager/RelationshipTypeManager.h"
#include "subsystem/HandleSubsystem.h"
#include "subsystem/TeleportSubsystem.h"
#include "subsystem/particle/ParticleSubsystem.h"

namespace inexor {
namespace entity {

struct type_info_less
{
    bool operator() (const std::type_info* lhs, const std::type_info* rhs) const
    {
        return lhs->before(*rhs) != 0;
    }
};

class EntitySystem;

typedef std::map<std::type_info const*, void *, type_info_less> TypenameToObject;
typedef std::map<std::type_info const*, void *, type_info_less>::iterator TypeMapIterator;

class TypeMap
{
    friend class EntitySystem;

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
        virtual ~EntitySystem();

        /**
         * Initializes the providers.
         */
        void InitProviders();

        /**
         * Initializes the subsystems.
         */
        void InitSubsystems();

        /**
         * Frame update (main thread).
         */
        void Update();

        /**
         * Cleanup at shutdown.
         */
        void Cleanup();

        /**
         * Called on a GFX reset. Each subsystem's Reset() method is called
         * for cleanup purposes.
         */
        void Reset();

        /**
         * Returns a typed reference to the concrete subsystem. You can
         * retrieve the subsystem with it's original type from everywhere.
         */
        template <typename T>
        T *GetSubsystem () const
        {
            return subsystemTypeMap.Get<T>();
        }

        /**
         * Save the current entity system.
         */
        void Save(std::string filename);

        /**
         * Loads a entity system from file.
         */
        void Load(std::string filename);

        /**
         * Reset timer.
         */
        void ResetTimer();

        /**
         * Sets the time unit.
         */
        void SetTimeUnit(double time_unit);

        /**
         * Returns the entity type manager which is responsible for
         * managing the entity types.
         */
        CefRefPtr<EntityTypeManager> GetEntityTypeManager();

        /**
         * Returns the relationship type manager which is responsible for
         * managing the relationship types.
         */
        CefRefPtr<RelationshipTypeManager> GetRelationshipTypeManager();

        /**
         * Returns the entity instance manager which is responsible for
         * managing the entity instances.
         */
        CefRefPtr<EntityInstanceManager> GetEntityInstanceManager();

        /**
         * Returns the relationship instance manager which is responsible for
         * managing the relationship instances.
         */
        CefRefPtr<RelationshipInstanceManager> GetRelationshipInstanceManager();

    private:

        /**
         * Frame calculation: The current frame millis.
         */
        int frame_millis;

        /**
         * Frame calculation: The last frame millis.
         */
        int frame_last_millis;

        /**
         * Frame calculation: The elapsed millis since the last frame.
         */
        int elapsed_millis;

        /**
         * The time unit in milliseconds. Normally set to 1000 for one
         * second.
         *
         * The time unit is used for timing calculations. In the particle
         * system a rate of 10 would mean to spawn 10 particles per time
         * unit. If the time unit is 1000 millis, 10 particles would be
         * spawned within a second. If the gamespeed is lowered the time
         * unit should be reduced, too.
         */
        double time_unit;

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
         * The list of subsystems to iterate over. Only the common API
         * provided by SubsystemBase is available.
         */
        std::vector<SubsystemBase*> subsystems;

        /**
         * The subsystem type map grants access to the real type of the
         * implemented subsystem.
         */
        TypeMap subsystemTypeMap;

        /**
         * The handle subsystem.
         */
        CefRefPtr<HandleSubsystem> handle_subsystem;

        /**
         * The teleport subsystem.
         */
        CefRefPtr<TeleportSubsystem> teleport_subsystem;

        /**
         * The particle subsystem.
         */
        CefRefPtr<particle::ParticleSubsystem> particle_subsystem;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntitySystem);
};

}
}

/**
 * Provide the entity system as global reference.
 */
extern CefRefPtr<inexor::entity::EntitySystem> entity_system;

#endif /* SRC_ENGINE_ENTITY_ENTITYSYSTEM_H_ */
