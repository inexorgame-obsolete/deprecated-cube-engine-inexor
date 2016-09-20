/*
 * VectorField.h
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_VECTORFIELD_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_VECTORFIELD_H_

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityInstance.hpp"
#include "inexor/particle/model/ParticleModel.hpp"
#include "inexor/util/Logging.hpp"
#include "inexor/muparser/muParser.h"

namespace inexor {
namespace entity {
namespace particle {

    class VectorField : public EntityFunction
    {
        public:

            VectorField(std::string expression);
            virtual ~VectorField();

            void Before(TimeStep time_step, EntityInstance* modifier);
            void After(TimeStep time_step, EntityInstance* modifier);

            void Execute(TimeStep time_step, EntityInstance* modifier, EntityInstance* particle);

        private:

            mu::Parser parser;
            int args;
            std::string expression;
            mu::value_type ix;
            mu::value_type iy;
            mu::value_type iz;

            void SetExpression(std::string expression);

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(VectorField);
    };

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_VECTORFIELD_H_ */
