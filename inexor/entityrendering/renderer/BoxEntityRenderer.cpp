/*
 * BoxEntityRenderer.cpp
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#include "BoxEntityRenderer.hpp"
#include "inexor/fpsgame/game.hpp"
#include "inexor/engine/engine.hpp"
#include "inexor/particle/model/ParticleModel.hpp"

using namespace inexor::entity::particle;

namespace inexor {
namespace entity {
namespace rendering {

    BoxEntityRenderer::BoxEntityRenderer() : EntityFunction(ENT_FUNC_BOX_ENTITY_RENDERER)
    {
    }

    BoxEntityRenderer::~BoxEntityRenderer()
    {
    }

    void BoxEntityRenderer::Before(TimeStep time_step, std::shared_ptr<EntityInstance> renderer_inst)
    {
        // Replace with Hannis code
    }

    AttributeRefPtr BoxEntityRenderer::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> renderer_inst, std::shared_ptr<EntityInstance> particle_inst)
    {
        // Replace with Hannis code
        return true;
    }

    void BoxEntityRenderer::After(TimeStep time_step, std::shared_ptr<EntityInstance> renderer_inst)
    {
        // Replace with Hannis code
    }

}
}
}
