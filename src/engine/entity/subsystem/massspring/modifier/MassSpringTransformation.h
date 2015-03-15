/*
 * MassSpringTransformation.h
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_MASSSPRING_MODIFIER_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_MASSSPRING_MODIFIER_H_

#include "../../../EntitySystemBase.h"
#include "../../../domain/graph/EntityFunction.h"
#include "../../../domain/graph/EntityInstance.h"
#include "../../../domain/graph/RelationshipInstance.h"
#include "../MassSpringModel.h"

namespace inexor {
namespace entity {
namespace massspring {

class MassSpringTransformation : public EntityFunction
{
    public:
        MassSpringTransformation();
        virtual ~MassSpringTransformation();

        void Execute(TimeStep time_step, RelationshipInstance* spring);

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(MassSpringTransformation);
};

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_MASSSPRING_MODIFIER_H_ */
