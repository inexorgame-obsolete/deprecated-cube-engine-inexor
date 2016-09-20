/*
 * Culling.h
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_CULLING_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_CULLING_H_

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityInstance.hpp"
#include "inexor/particle/model/ParticleModel.hpp"

namespace inexor {
namespace entity {
namespace particle {

    class Culling : public EntityFunction
    {
        public:

            Culling();
            virtual ~Culling();

            void Execute(TimeStep time_step, EntityInstance* modifier, EntityInstance* particle);

        private:

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(Culling);
    };

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_CULLING_H_ */
