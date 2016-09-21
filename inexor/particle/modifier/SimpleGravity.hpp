/*
 * SimpleGravity.h
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_SIMPLE_GRAVITY_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_SIMPLE_GRAVITY_H_

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityInstance.hpp"
#include "inexor/particle/model/ParticleModel.hpp"

namespace inexor {
namespace entity {
namespace particle {

    class SimpleGravity : public EntityFunction
    {
        public:

            SimpleGravity();
            virtual ~SimpleGravity();

            void Before(TimeStep time_step, std::shared_ptr<EntityInstance> modifier);
            void Execute(TimeStep time_step, std::shared_ptr<EntityInstance> modifier, std::shared_ptr<EntityInstance> particle);

        private:

            float mass;
            float gravity;
            float dz;

    };

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_SIMPLE_GRAVITY_H_ */
