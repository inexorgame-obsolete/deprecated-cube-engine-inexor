/*
 * Immortal.h
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_IMMORTAL_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_IMMORTAL_H_

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityInstance.hpp"
#include "inexor/particle/model/ParticleModel.hpp"

namespace inexor {
namespace entity {
namespace particle {

    class Immortal : public EntityFunction
    {
        public:

            Immortal();
            virtual ~Immortal();

            void Execute(TimeStep time_step, EntityInstance* modifier, EntityInstance* particle);

        private:

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(Immortal);
    };

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_IMMORTAL_H_ */
