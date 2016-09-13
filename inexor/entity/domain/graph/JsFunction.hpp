/*
 * JsFunction.h
 *
 *  Created on: 30.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_DOMAIN_GRAPH_JSFUNCTION_H_
#define SRC_ENGINE_ENTITY_DOMAIN_GRAPH_JSFUNCTION_H_

#include "../../EntitySystemBase.hpp"
#include "EntityFunction.hpp"

namespace inexor {
namespace entity {

class JsFunction : public EntityFunction
{
    public:
        JsFunction(std::string name, std::string callback_name);
        virtual ~JsFunction();

        std::string GetCallbackName();
        void SetCallbackName(std::string callback_name);

    private:
        std::string callback_name;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(JsFunction);

};

}
}

#endif /* SRC_ENGINE_ENTITY_DOMAIN_GRAPH_JSFUNCTION_H_ */
