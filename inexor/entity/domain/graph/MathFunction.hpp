/*
 * MathFunction.h
 *
 *  Created on: 30.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_DOMAIN_GRAPH_MATHFUNCTION_H_
#define SRC_ENGINE_ENTITY_DOMAIN_GRAPH_MATHFUNCTION_H_

#include "../../EntitySystemBase.hpp"
#include "EntityFunction.hpp"

namespace inexor {
namespace entity {

    class MathFunction : public EntityFunction
    {
        public:

            MathFunction(std::string name, std::string expression);
            virtual ~MathFunction();

            std::string GetExpression();
            void SetExpression(std::string expression);

        private:

            std::string expression;

    };

}
}

#endif /* SRC_ENGINE_ENTITY_DOMAIN_GRAPH_MATHFUNCTION_H_ */
