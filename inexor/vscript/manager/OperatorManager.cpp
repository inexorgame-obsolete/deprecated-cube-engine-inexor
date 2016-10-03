#include "OperatorManager.hpp"

namespace inexor {
namespace vscript {

    OperatorManager::OperatorManager(std::shared_ptr<EntityTypeManager> entity_type_manager,
                               std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                               std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                               std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager)
      : entity_type_manager(entity_type_manager),
        entity_instance_manager(entity_instance_manager),
        relationship_type_manager(relationship_type_manager),
        relationship_instance_manager(relationship_instance_manager)
    {
        parent_operator_type = entity_type_manager->Create(ENT_TYPE_OPERATOR, true, true);
    }

    OperatorManager::~OperatorManager()
    {
    }

    void OperatorManager::Update(TimeStep time_step)
    {
        spdlog::get("global")->info() << "OperatorManager::Update";
    }

    void OperatorManager::Cleanup()
    {
        spdlog::get("global")->info() << "OperatorManager::Cleanup";
    }

    void OperatorManager::Reset()
    {
        spdlog::get("global")->info() << "OperatorManager::Reset";
    }

    TypeRefPtr<EntityType> OperatorManager::CreateOperatorType(std::string name, FunctionRefPtr propagation_function)
    {
        TypeRefPtr<EntityType> operator_type = entity_type_manager->Create(name, true, true, parent_operator_type);
        operator_type[ENT_TYPE_ATTR_PROPAGATE]->functionVal = propagation_function;
        operator_types[name] = operator_type;
        return operator_type;
    }

    InstanceRefPtr<EntityInstance> OperatorManager::CreateOperator(TypeRefPtr<EntityType> operator_entity_type, double x, double y, double z)
    {
        InstanceRefPtr<EntityInstance> operator_entity_instance = entity_instance_manager->Create(operator_entity_type);
        operator_entity_instance["x"] = x;
        operator_entity_instance["y"] = y;
        operator_entity_instance["z"] = z;
        operator_instances.push_back(operator_entity_instance);
        return operator_entity_instance;
    }

    void OperatorManager::RemoveOperator(InstanceRefPtr<EntityInstance>)
    {
        // TODO: implement
        // Remove instance and all relationships
    }

}
}
