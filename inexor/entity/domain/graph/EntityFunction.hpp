/*
 * EntityAction.h
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYFUNCTION_H_
#define SRC_ENGINE_ENTITY_ENTITYFUNCTION_H_

#include "../../EntitySystemBase.hpp"
#include "../TimeStep.hpp"

namespace inexor {
namespace entity {

    class EntityType;
    class RelationshipType;
    class EntityInstance;
    class RelationshipInstance;

    class EntityFunction
    {
        public:
            /**
             * Constructs an entity function without a signature. This means that
             * the function has no implementation or provides multiple
             * implementations.
             */
            EntityFunction(std::string name);

            /**
             * Constructs an entity function with the given signature.
             * Derived classes specifies how to use them.
             */
            EntityFunction(std::string name, int signature);

            virtual ~EntityFunction();

            /**
             * Returns the name of the entity function.
             */
            std::string GetName();

            /**
             * Returns the signature of the entity function.
             */
            int GetSignature();

            virtual void Before(TimeStep time_step, EntityInstance* inst);
            virtual void After(TimeStep time_step, EntityInstance* inst);

            /*
             * Signature 0: Execute function.
             * @param time_step The timing information.
             */
            virtual void Execute(TimeStep time_step);

            /*
             * Signature 1: Execute function.
             * @param time_step The timing information.
             * @param type The entity type.
             */
            virtual void Execute(TimeStep time_step, EntityType* type);

            // Signature 2
            virtual void Execute(TimeStep time_step, EntityType* type, EntityInstance* inst);

            // Signature 3
            virtual void Execute(TimeStep time_step, EntityInstance* inst);

            // Signature 4
            virtual void Execute(TimeStep time_step, EntityInstance* inst, RelationshipType* rel_type);

            // Signature 5
            virtual void Execute(TimeStep time_step, EntityInstance* inst, RelationshipInstance* rel_inst);

            // Signature 6
            virtual void Execute(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2);

            // Signature 7
            virtual void Execute(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2, EntityInstance* inst_3);

            // Signature 8
            virtual void Execute(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2, RelationshipType* rel_type);

            // Signature 9
            virtual void Execute(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2, RelationshipInstance* rel_inst);

            // Signature 10
            virtual void Execute(TimeStep time_step, RelationshipType* type);

            // Signature 11
            virtual void Execute(TimeStep time_step, RelationshipType* type, RelationshipInstance* inst);

            // Signature 12
            virtual void Execute(TimeStep time_step, RelationshipInstance* inst);

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

        private:
            std::string name;
            int signature;

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(EntityFunction);

    };

}
}

#endif /* SRC_ENGINE_ENTITY_ENTITYFUNCTION_H_ */
