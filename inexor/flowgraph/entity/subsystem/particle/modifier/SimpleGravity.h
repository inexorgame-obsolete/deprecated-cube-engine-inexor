/*
 * SimpleGravity.h
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_SIMPLE_GRAVITY_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_SIMPLE_GRAVITY_H_

#include "../../../EntitySystemBase.h"
#include "../../../domain/graph/EntityFunction.h"
#include "../../../domain/graph/EntityInstance.h"
#include "../ParticleModel.h"

namespace inexor {
namespace entity {
namespace particle {

class SimpleGravity : public EntityFunction
{
    public:
        SimpleGravity();
        virtual ~SimpleGravity();

        void Before(TimeStep time_step, EntityInstance* modifier);
        void Execute(TimeStep time_step, EntityInstance* modifier, EntityInstance* particle);

    private:

        float mass;
        float gravity;
        float dz;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(SimpleGravity);
};

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_SIMPLE_GRAVITY_H_ */
