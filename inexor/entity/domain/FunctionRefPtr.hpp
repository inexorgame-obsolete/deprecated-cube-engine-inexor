/*
 * FunctionRefPtr.h
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

    class FunctionRefPtr : public CefRefPtr<EntityFunction> 
    {
        public:

            typedef CefRefPtr<EntityFunction> parent;

            FunctionRefPtr();
            FunctionRefPtr(EntityFunction* p);
            FunctionRefPtr(const CefRefPtr<EntityFunction>& r);

            template <typename U>
            FunctionRefPtr(const CefRefPtr<U>& r) : parent(r) {
            }

            void operator()(TimeStep time_step);
            void operator()(TimeStep time_step, EntityType* type);
            void operator()(TimeStep time_step, EntityType* type, EntityInstance* inst);
            void operator()(TimeStep time_step, EntityInstance* inst);
            void operator()(TimeStep time_step, EntityInstance* inst, RelationshipType* rel_type);
            void operator()(TimeStep time_step, EntityInstance* inst, RelationshipInstance* rel_inst);
            void operator()(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2);
            void operator()(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2, EntityInstance* inst_3);
            void operator()(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2, RelationshipType* rel_type);
            void operator()(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2, RelationshipInstance* rel_inst);
            void operator()(TimeStep time_step, RelationshipType* type);
            void operator()(TimeStep time_step, RelationshipType* type, RelationshipInstance* inst);
            void operator()(TimeStep time_step, RelationshipInstance* inst);

    };

}
}

#endif /* SRC_ENGINE_ENTITY_DOMAIN_FUNCTIONREFPTR_H_ */
