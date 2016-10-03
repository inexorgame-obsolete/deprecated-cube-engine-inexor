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
        // TODO: document this in detail
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
    AttributeRefPtr EntityFunction::Execute(TimeStep time_step) { return true; }
    AttributeRefPtr EntityFunction::Execute(TimeStep time_step, std::shared_ptr<EntityType> type) { return true; }
    AttributeRefPtr EntityFunction::Execute(TimeStep time_step, std::shared_ptr<EntityType> type, std::shared_ptr<EntityInstance> inst) { return true; }
    AttributeRefPtr EntityFunction::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> inst) { return true; }
    AttributeRefPtr EntityFunction::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> inst, std::shared_ptr<RelationshipType> rel_type) { return true; }
    AttributeRefPtr EntityFunction::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> inst, std::shared_ptr<RelationshipInstance> rel_inst) { return true; }
    AttributeRefPtr EntityFunction::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2) { return true; }
    AttributeRefPtr EntityFunction::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<EntityInstance> inst_3) { return true; }
    AttributeRefPtr EntityFunction::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<RelationshipType> rel_type) { return true; }
    AttributeRefPtr EntityFunction::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<RelationshipInstance> rel_inst) { return true; }
    AttributeRefPtr EntityFunction::Execute(TimeStep time_step, std::shared_ptr<RelationshipType> type) { return true; }
    AttributeRefPtr EntityFunction::Execute(TimeStep time_step, std::shared_ptr<RelationshipType> type, std::shared_ptr<RelationshipInstance> inst) { return true; }
    AttributeRefPtr EntityFunction::Execute(TimeStep time_step, std::shared_ptr<RelationshipInstance> inst) { return true; }

    // Calls the overwritten method, if there is any
    AttributeRefPtr EntityFunction::operator()(TimeStep time_step) { return Execute(time_step); }
    AttributeRefPtr EntityFunction::operator()(TimeStep time_step, std::shared_ptr<EntityType> type) { return Execute(time_step, type); }
    AttributeRefPtr EntityFunction::operator()(TimeStep time_step, std::shared_ptr<EntityType> type, std::shared_ptr<EntityInstance> inst) { return Execute(time_step, type, inst); }
    AttributeRefPtr EntityFunction::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst) { return Execute(time_step, inst); }
    AttributeRefPtr EntityFunction::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst, std::shared_ptr<RelationshipType> rel_type) { return Execute(time_step, inst, rel_type); }
    AttributeRefPtr EntityFunction::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst, std::shared_ptr<RelationshipInstance> rel_inst) { return Execute(time_step, inst, rel_inst); }
    AttributeRefPtr EntityFunction::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2) { return Execute(time_step, inst_1, inst_2); }
    AttributeRefPtr EntityFunction::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<EntityInstance> inst_3) { return Execute(time_step, inst_1, inst_2, inst_3); }
    AttributeRefPtr EntityFunction::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<RelationshipType> rel_type) { return Execute(time_step, inst_1, inst_2, rel_type); }
    AttributeRefPtr EntityFunction::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<RelationshipInstance> rel_inst) { return Execute(time_step, inst_1, inst_2, rel_inst); }
    AttributeRefPtr EntityFunction::operator()(TimeStep time_step, std::shared_ptr<RelationshipType> type) { return Execute(time_step, type); }
    AttributeRefPtr EntityFunction::operator()(TimeStep time_step, std::shared_ptr<RelationshipType> type, std::shared_ptr<RelationshipInstance> inst) { return Execute(time_step, type, inst); }
    AttributeRefPtr EntityFunction::operator()(TimeStep time_step, std::shared_ptr<RelationshipInstance> inst) { return Execute(time_step, inst); }

}
}
