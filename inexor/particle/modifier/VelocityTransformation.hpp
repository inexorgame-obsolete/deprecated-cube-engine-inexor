/*
 * VelocityTransformation.h
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_VELOCITYTRANSFORMATION_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_VELOCITYTRANSFORMATION_H_

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityInstance.hpp"
#include "inexor/particle/model/ParticleModel.hpp"

namespace inexor {
namespace entity {
namespace particle {

    class VelocityTransformation : public EntityFunction
    {
        public:

            VelocityTransformation();
            virtual ~VelocityTransformation();

            void Execute(TimeStep time_step, std::shared_ptr<EntityInstance> modifier, std::shared_ptr<EntityInstance> particle);

    };

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_VELOCITYTRANSFORMATION_H_ */
