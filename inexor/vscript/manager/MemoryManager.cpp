#include "MemoryManager.hpp"

namespace inexor {
namespace vscript {

    MemoryManager::MemoryManager(std::shared_ptr<EntityTypeManager> entity_type_manager,
                               std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                               std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                               std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager)
      : entity_type_manager(entity_type_manager),
        entity_instance_manager(entity_instance_manager),
        relationship_type_manager(relationship_type_manager),
        relationship_instance_manager(relationship_instance_manager)
    {
        parent_memory_type = entity_type_manager->Create(ENT_TYPE_MEMORY, true, true);
    }

    MemoryManager::~MemoryManager()
    {
    }

    void MemoryManager::Update(TimeStep time_step)
    {
        spdlog::get("global")->info() << "MemoryManager::Update";
    }

    void MemoryManager::Cleanup()
    {
        spdlog::get("global")->info() << "MemoryManager::Cleanup";
    }

    void MemoryManager::Reset()
    {
        spdlog::get("global")->info() << "MemoryManager::Reset";
    }

    TypeRefPtr<EntityType> MemoryManager::CreateMemoryType(std::string name, FunctionRefPtr propagation_function)
    {
        TypeRefPtr<EntityType> memory_type = entity_type_manager->Create(name, true, true, parent_memory_type);
        memory_type[ENT_TYPE_ATTR_PROPAGATE]->functionVal = propagation_function;
        memory_types[name] = memory_type;
        return memory_type;
    }

    InstanceRefPtr<EntityInstance> MemoryManager::CreateMemory(TypeRefPtr<EntityType> memory_entity_type, double x, double y, double z)
    {
        InstanceRefPtr<EntityInstance> memory_entity_instance = entity_instance_manager->Create(memory_entity_type);
        memory_entity_instance["x"] = x;
        memory_entity_instance["y"] = y;
        memory_entity_instance["z"] = z;
        memory_instances.push_back(memory_entity_instance);
        return memory_entity_instance;
    }

    void MemoryManager::RemoveMemory(InstanceRefPtr<EntityInstance>)
    {
        // TODO: implement
        // Remove instance and all relationships
    }

}
}
