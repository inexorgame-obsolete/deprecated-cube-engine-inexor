#include "AreaManager.hpp"

namespace inexor {
namespace vscript {

    AreaManager::AreaManager(std::shared_ptr<EntityTypeManager> entity_type_manager,
                               std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                               std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                               std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager)
      : entity_type_manager(entity_type_manager),
        entity_instance_manager(entity_instance_manager),
        relationship_type_manager(relationship_type_manager),
        relationship_instance_manager(relationship_instance_manager)
    {
        parent_area_type = entity_type_manager->Create(ENT_TYPE_AREA, true, true);
    }

    AreaManager::~AreaManager()
    {
    }

    void AreaManager::Update(TimeStep time_step)
    {
        spdlog::get("global")->info() << "AreaManager::Update";
    }

    void AreaManager::Cleanup()
    {
        spdlog::get("global")->info() << "AreaManager::Cleanup";
    }

    void AreaManager::Reset()
    {
        spdlog::get("global")->info() << "AreaManager::Reset";
    }

    TypeRefPtr<EntityType> AreaManager::CreateAreaType(std::string name, FunctionRefPtr propagation_function)
    {
        TypeRefPtr<EntityType> area_type = entity_type_manager->Create(name, true, true, parent_area_type);
        area_type[ENT_TYPE_ATTR_PROPAGATE]->functionVal = propagation_function;
        area_types[name] = area_type;
        return area_type;
    }

    InstanceRefPtr<EntityInstance> AreaManager::CreateArea(TypeRefPtr<EntityType> area_entity_type, double x, double y, double z)
    {
        InstanceRefPtr<EntityInstance> area_entity_instance = entity_instance_manager->Create(area_entity_type);
        area_entity_instance["x"] = x;
        area_entity_instance["y"] = y;
        area_entity_instance["z"] = z;
        area_instances.push_back(area_entity_instance);
        return area_entity_instance;
    }

    void AreaManager::RemoveArea(InstanceRefPtr<EntityInstance>)
    {
        // TODO: implement
        // Remove instance and all relationships
    }

}
}
