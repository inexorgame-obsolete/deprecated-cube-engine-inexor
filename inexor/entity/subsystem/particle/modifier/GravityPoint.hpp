/*
 * GravityPoint.h
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_GRAVITYPOINT_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_GRAVITYPOINT_H_

#include "../../../EntitySystemBase.hpp"
#include "../../../domain/graph/EntityFunction.hpp"
#include "../../../domain/graph/EntityInstance.hpp"
#include "../ParticleModel.hpp"

namespace inexor {
namespace entity {
namespace particle {

    class GravityPoint : public EntityFunction
    {
        public:

            GravityPoint();
            virtual ~GravityPoint();

            void Execute(TimeStep time_step, EntityInstance* modifier, EntityInstance* particle);

        private:

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(GravityPoint);
    };

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_GRAVITYPOINT_H_ */
