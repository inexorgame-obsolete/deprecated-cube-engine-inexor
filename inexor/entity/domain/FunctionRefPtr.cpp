/*
 * FunctionRefPtr.cpp
 *
 *  Created on: 29.01.2015
 *      Author: aschaeffer
 */

#include "FunctionRefPtr.hpp"
#include "TypeBase.hpp"
#include "graph/EntityType.hpp"
#include "graph/RelationshipType.hpp"
#include "graph/EntityInstance.hpp"
#include "graph/EntityAttribute.hpp"
#include "graph/RelationshipInstance.hpp"
#include "graph/EntityAttribute.hpp"
#include "graph/EntityFunction.hpp"

namespace inexor {
namespace entity {

    FunctionRefPtr::FunctionRefPtr() : parent()
    {
    }

    FunctionRefPtr::FunctionRefPtr(EntityFunction* p) : parent(p)
    {
    }

    FunctionRefPtr::FunctionRefPtr(const std::shared_ptr<EntityFunction>& r) : parent(r)
    {
    }

    AttributeRefPtr FunctionRefPtr::operator()(TimeStep time_step)
    {
        return get()->Execute(time_step);
    }

    AttributeRefPtr FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityType> type)
    {
        return get()->Execute(time_step, type);
    }

    AttributeRefPtr FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityType> type, std::shared_ptr<EntityInstance> inst)
    {
        return get()->Execute(time_step, type, inst);
    }

    AttributeRefPtr FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst)
    {
        return get()->Execute(time_step, inst);
    }

    AttributeRefPtr FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst, std::shared_ptr<RelationshipType> rel_type)
    {
        return get()->Execute(time_step, inst, rel_type);
    }

    AttributeRefPtr FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst, std::shared_ptr<RelationshipInstance> rel_inst)
    {
        return get()->Execute(time_step, inst, rel_inst);
    }

    AttributeRefPtr FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2)
    {
        return get()->Execute(time_step, inst_1, inst_2);
    }

    AttributeRefPtr FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<EntityInstance> inst_3)
    {
        return get()->Execute(time_step, inst_1, inst_2, inst_3);
    }

    AttributeRefPtr FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<RelationshipType> rel_type)
    {
        return get()->Execute(time_step, inst_1, inst_2, rel_type);
    }

    AttributeRefPtr FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<RelationshipInstance> rel_inst)
    {
        return get()->Execute(time_step, inst_1, inst_2, rel_inst);
    }

    AttributeRefPtr FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<RelationshipType> type)
    {
        return get()->Execute(time_step, type);
    }

    AttributeRefPtr FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<RelationshipType> type, std::shared_ptr<RelationshipInstance> inst)
    {
        return get()->Execute(time_step, type, inst);
    }

    AttributeRefPtr FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<RelationshipInstance> inst)
    {
        return get()->Execute(time_step, inst);
    }

}
}
