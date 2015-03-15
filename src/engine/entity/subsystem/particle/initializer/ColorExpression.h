/*
 * ColorExpression.h
 *
 *  Created on: 08.03.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_INITIALIZER_COLOR_EXPRESSION_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_INITIALIZER_COLOR_EXPRESSION_H_

#include "../ExpressionBase.h"
#include "../../../EntitySystemBase.h"
#include "../../../domain/graph/EntityFunction.h"
#include "../../../domain/graph/EntityInstance.h"
#include "../ParticleModel.h"
#include "muParser.h"

namespace inexor {
namespace entity {
namespace particle {

class ColorExpression : public EntityFunction
{
    public:
        ColorExpression(std::string expression);
        virtual ~ColorExpression();

        void Execute(TimeStep time_step, EntityInstance* emitter, EntityInstance* initializer, EntityInstance* particle);

    private:
        mu::Parser parser;
        int args;
        std::string expression;
        mu::value_type time;
        mu::value_type sequence_number;
        mu::value_type emitter_x;
        mu::value_type emitter_y;
        mu::value_type emitter_z;
        mu::value_type particle_x;
        mu::value_type particle_y;
        mu::value_type particle_z;

        void SetExpression(std::string expression);

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(ColorExpression);
};

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_INITIALIZER_COLOR_EXPRESSION_H_ */
