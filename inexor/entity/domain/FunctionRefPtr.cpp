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

    void FunctionRefPtr::operator()(TimeStep time_step)
    {
        get()->Execute(time_step);
    }

    void FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityType> type)
    {
        get()->Execute(time_step, type);
    }

    void FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityType> type, std::shared_ptr<EntityInstance> inst)
    {
        get()->Execute(time_step, type, inst);
    }

    void FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst)
    {
        get()->Execute(time_step, inst);
    }

    void FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst, std::shared_ptr<RelationshipType> rel_type)
    {
        get()->Execute(time_step, inst, rel_type);
    }

    void FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst, std::shared_ptr<RelationshipInstance> rel_inst)
    {
        get()->Execute(time_step, inst, rel_inst);
    }

    void FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2)
    {
        get()->Execute(time_step, inst_1, inst_2);
    }

    void FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<EntityInstance> inst_3)
    {
        get()->Execute(time_step, inst_1, inst_2, inst_3);
    }

    void FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<RelationshipType> rel_type)
    {
        get()->Execute(time_step, inst_1, inst_2, rel_type);
    }

    void FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<RelationshipInstance> rel_inst)
    {
        get()->Execute(time_step, inst_1, inst_2, rel_inst);
    }

    void FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<RelationshipType> type)
    {
        get()->Execute(time_step, type);
    }

    void FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<RelationshipType> type, std::shared_ptr<RelationshipInstance> inst)
    {
        get()->Execute(time_step, type, inst);
    }

    void FunctionRefPtr::operator()(TimeStep time_step, std::shared_ptr<RelationshipInstance> inst)
    {
        get()->Execute(time_step, inst);
    }

}
}
