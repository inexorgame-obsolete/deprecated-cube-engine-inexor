/*
 * EntityAction.cpp
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#include "EntityFunction.hpp"
#include "EntityType.hpp"
#include "RelationshipType.hpp"
#include "EntityInstance.hpp"
#include "RelationshipInstance.hpp"

namespace inexor {
namespace entity {

    EntityFunction::EntityFunction(std::string name) : name(name), signature(-1)
    {
        // No signature
    }

    EntityFunction::EntityFunction(std::string name, int signature) : name(name), signature(signature)
    {
        // Sets the signature of the entity function
    }

    EntityFunction::~EntityFunction()
    {
    }

    std::string EntityFunction::GetName()
    {
        return name;
    }

    int EntityFunction::GetSignature()
    {
        return signature;
    }

    void EntityFunction::Before(TimeStep time_step, std::shared_ptr<EntityInstance> inst) {}
    void EntityFunction::After(TimeStep time_step, std::shared_ptr<EntityInstance> inst) {}

    // Default: do nothing
    void EntityFunction::Execute(TimeStep time_step) {}
    void EntityFunction::Execute(TimeStep time_step, std::shared_ptr<EntityType> type) {}
    void EntityFunction::Execute(TimeStep time_step, std::shared_ptr<EntityType> type, std::shared_ptr<EntityInstance> inst) {}
    void EntityFunction::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> inst) {}
    void EntityFunction::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> inst, std::shared_ptr<RelationshipType> rel_type) {}
    void EntityFunction::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> inst, std::shared_ptr<RelationshipInstance> rel_inst) {}
    void EntityFunction::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2) {}
    void EntityFunction::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<EntityInstance> inst_3) {}
    void EntityFunction::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<RelationshipType> rel_type) {}
    void EntityFunction::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<RelationshipInstance> rel_inst) {}
    void EntityFunction::Execute(TimeStep time_step, std::shared_ptr<RelationshipType> type) {}
    void EntityFunction::Execute(TimeStep time_step, std::shared_ptr<RelationshipType> type, std::shared_ptr<RelationshipInstance> inst) {}
    void EntityFunction::Execute(TimeStep time_step, std::shared_ptr<RelationshipInstance> inst) {}

    // Calls the overwritten method, if there is any
    void EntityFunction::operator()(TimeStep time_step) { Execute(time_step); }
    void EntityFunction::operator()(TimeStep time_step, std::shared_ptr<EntityType> type) { Execute(time_step, type); }
    void EntityFunction::operator()(TimeStep time_step, std::shared_ptr<EntityType> type, std::shared_ptr<EntityInstance> inst) { Execute(time_step, type, inst); }
    void EntityFunction::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst) { Execute(time_step, inst); }
    void EntityFunction::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst, std::shared_ptr<RelationshipType> rel_type) { Execute(time_step, inst, rel_type); }
    void EntityFunction::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst, std::shared_ptr<RelationshipInstance> rel_inst) { Execute(time_step, inst, rel_inst); }
    void EntityFunction::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2) { Execute(time_step, inst_1, inst_2); }
    void EntityFunction::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<EntityInstance> inst_3) { Execute(time_step, inst_1, inst_2, inst_3); }
    void EntityFunction::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<RelationshipType> rel_type) { Execute(time_step, inst_1, inst_2, rel_type); }
    void EntityFunction::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<RelationshipInstance> rel_inst) { Execute(time_step, inst_1, inst_2, rel_inst); }
    void EntityFunction::operator()(TimeStep time_step, std::shared_ptr<RelationshipType> type) { Execute(time_step, type); }
    void EntityFunction::operator()(TimeStep time_step, std::shared_ptr<RelationshipType> type, std::shared_ptr<RelationshipInstance> inst) { Execute(time_step, type, inst); }
    void EntityFunction::operator()(TimeStep time_step, std::shared_ptr<RelationshipInstance> inst) { Execute(time_step, inst); }

}
}
