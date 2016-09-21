/*
 * PlayerCollide.h
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#ifndef INEXOR_PARTICLE_MODIFIER_PLAYER_COLLIDE_HEADER
#define INEXOR_PARTICLE_MODIFIER_PLAYER_COLLIDE_HEADER

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityInstance.hpp"
#include "inexor/particle/model/ParticleModel.hpp"

// extern bool collide(physent *d, const vec &dir, float cutoff, bool playercol);
extern bool plcollide(physent *d, const vec &dir);

struct fpsent;

extern fpsent *player1;

namespace inexor {
namespace entity {
namespace particle {

    class PlayerCollide : public EntityFunction
    {
        public:

            PlayerCollide();
            virtual ~PlayerCollide();

            void Execute(TimeStep time_step, std::shared_ptr<EntityInstance> modifier, std::shared_ptr<EntityInstance> particle);

    };

}
}
}

#endif /* INEXOR_PARTICLE_MODIFIER_PLAYER_COLLIDE_HEADER */
