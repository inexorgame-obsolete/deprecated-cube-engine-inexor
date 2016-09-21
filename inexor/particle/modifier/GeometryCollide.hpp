/*
 * GeometryCollide.h
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_GEOMETRY_COLLIDE_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_GEOMETRY_COLLIDE_H_

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityInstance.hpp"
#include "inexor/particle/model/ParticleModel.hpp"

extern bool collide(physent *d, const vec &dir, float cutoff, bool playercol);

namespace inexor {
namespace entity {
namespace particle {

    class GeometryCollide : public EntityFunction
    {
        public:

            GeometryCollide();
            virtual ~GeometryCollide();

            void Execute(TimeStep time_step, std::shared_ptr<EntityInstance> modifier, std::shared_ptr<EntityInstance> particle);

    };

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_GEOMETRY_COLLIDE_H_ */
