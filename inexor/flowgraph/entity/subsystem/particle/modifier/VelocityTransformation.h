/*
 * VelocityTransformation.h
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_VELOCITYTRANSFORMATION_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_VELOCITYTRANSFORMATION_H_

#include "../../../EntitySystemBase.h"
#include "../../../domain/graph/EntityFunction.h"
#include "../../../domain/graph/EntityInstance.h"
#include "../ParticleModel.h"

namespace inexor {
namespace entity {
namespace particle {

class VelocityTransformation : public EntityFunction
{
    public:
        VelocityTransformation();
        virtual ~VelocityTransformation();

        void Execute(TimeStep time_step, EntityInstance* modifier, EntityInstance* particle);

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(VelocityTransformation);
};

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_VELOCITYTRANSFORMATION_H_ */
