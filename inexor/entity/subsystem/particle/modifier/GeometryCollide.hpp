/*
 * GeometryCollide.h
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_GEOMETRY_COLLIDE_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_GEOMETRY_COLLIDE_H_

#include "../../../EntitySystemBase.hpp"
#include "../../../domain/graph/EntityFunction.hpp"
#include "../../../domain/graph/EntityInstance.hpp"
#include "../ParticleModel.hpp"

extern bool collide(physent *d, const vec &dir, float cutoff, bool playercol);

namespace inexor {
namespace entity {
namespace particle {

    class GeometryCollide : public EntityFunction
    {
        public:

            GeometryCollide();
            virtual ~GeometryCollide();

            void Execute(TimeStep time_step, EntityInstance* modifier, EntityInstance* particle);

        private:

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(GeometryCollide);
    };

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_GEOMETRY_COLLIDE_H_ */
