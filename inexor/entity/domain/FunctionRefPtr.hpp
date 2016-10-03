/*
 * FunctionRefPtr.hpp
 *
 *  Created on: 29.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_DOMAIN_FUNCTIONREFPTR_H_
#define SRC_ENGINE_ENTITY_DOMAIN_FUNCTIONREFPTR_H_

#include "../EntitySystemBase.hpp"
#include "TimeStep.hpp"
#include "graph/EntityFunction.hpp"

namespace inexor {
namespace entity {

    class TypeBase;
    class EntityType;
    class RelationshipType;
    class EntityInstance;
    class RelationshipInstance;

    /**
     *
     */
    class FunctionRefPtr : public std::shared_ptr<EntityFunction>
    {
        public:

            typedef std::shared_ptr<EntityFunction> parent;

            /**
             *
             */
            FunctionRefPtr();
            FunctionRefPtr(EntityFunction* p);
            FunctionRefPtr(const std::shared_ptr<EntityFunction>& r);

            /**
             *
             */
            template <typename U>
            FunctionRefPtr(const std::shared_ptr<U>& r) : parent(r)
            {
            }

            /**
             *
             */
            AttributeRefPtr operator()(TimeStep time_step);
            AttributeRefPtr operator()(TimeStep time_step, std::shared_ptr<EntityType> type);
            AttributeRefPtr operator()(TimeStep time_step, std::shared_ptr<EntityType> type, std::shared_ptr<EntityInstance> inst);
            AttributeRefPtr operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst);
            AttributeRefPtr operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst, std::shared_ptr<RelationshipType> rel_type);
            AttributeRefPtr operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst, std::shared_ptr<RelationshipInstance> rel_inst);
            AttributeRefPtr operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2);
            AttributeRefPtr operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<EntityInstance> inst_3);
            AttributeRefPtr operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<RelationshipType> rel_type);
            AttributeRefPtr operator()(TimeStep time_step, std::shared_ptr<EntityInstance> inst_1, std::shared_ptr<EntityInstance> inst_2, std::shared_ptr<RelationshipInstance> rel_inst);
            AttributeRefPtr operator()(TimeStep time_step, std::shared_ptr<RelationshipType> type);
            AttributeRefPtr operator()(TimeStep time_step, std::shared_ptr<RelationshipType> type, std::shared_ptr<RelationshipInstance> inst);
            AttributeRefPtr operator()(TimeStep time_step, std::shared_ptr<RelationshipInstance> inst);

    };

}
}

#endif /* SRC_ENGINE_ENTITY_DOMAIN_FUNCTIONREFPTR_H_ */
