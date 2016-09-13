/*
 * SimpleGravity.h
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_SIMPLE_GRAVITY_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_SIMPLE_GRAVITY_H_

#include "../../../EntitySystemBase.hpp"
#include "../../../domain/graph/EntityFunction.hpp"
#include "../../../domain/graph/EntityInstance.hpp"
#include "../ParticleModel.hpp"

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
