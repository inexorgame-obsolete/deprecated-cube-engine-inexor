/*
 * EntityAction.h
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYFUNCTION_H_
#define SRC_ENGINE_ENTITY_ENTITYFUNCTION_H_

#include "../../EntitySystemBase.h"
#include "../TimeStep.h"

class EntityType;
class RelationshipType;
class EntityInstance;
class RelationshipInstance;

class EntityFunction
{
    public:
        EntityFunction(std::string name);
        virtual ~EntityFunction();

        std::string GetName();

        virtual void Execute(TimeStep time_step);
        virtual void Execute(TimeStep time_step, EntityType* type);
        virtual void Execute(TimeStep time_step, EntityType* type, EntityInstance* inst);
        virtual void Execute(TimeStep time_step, EntityInstance* inst);
        virtual void Execute(TimeStep time_step, EntityInstance* inst, RelationshipType* rel_type);
        virtual void Execute(TimeStep time_step, EntityInstance* inst, RelationshipInstance* rel_inst);
        virtual void Execute(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2);
        virtual void Execute(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2, RelationshipType* rel_type);
        virtual void Execute(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2, RelationshipInstance* rel_inst);
        virtual void Execute(TimeStep time_step, RelationshipType* type);
        virtual void Execute(TimeStep time_step, RelationshipType* type, RelationshipInstance* inst);
        virtual void Execute(TimeStep time_step, RelationshipInstance* inst);

        void operator()(TimeStep time_step);
        void operator()(TimeStep time_step, EntityType* type);
        void operator()(TimeStep time_step, EntityType* type, EntityInstance* inst);
        void operator()(TimeStep time_step, EntityInstance* inst);
        void operator()(TimeStep time_step, EntityInstance* inst, RelationshipType* rel_type);
        void operator()(TimeStep time_step, EntityInstance* inst, RelationshipInstance* rel_inst);
        void operator()(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2);
        void operator()(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2, RelationshipType* rel_type);
        void operator()(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2, RelationshipInstance* rel_inst);
        void operator()(TimeStep time_step, RelationshipType* type);
        void operator()(TimeStep time_step, RelationshipType* type, RelationshipInstance* inst);
        void operator()(TimeStep time_step, RelationshipInstance* inst);

    private:
        std::string name;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityFunction);

};

#endif /* SRC_ENGINE_ENTITY_ENTITYFUNCTION_H_ */
