/*
 * BoxEntityRenderer.cpp
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#include "BoxEntityRenderer.hpp"
#include "inexor/fpsgame/game.hpp"
#include "inexor/engine/engine.hpp"

namespace inexor {
namespace entity {
namespace rendering {

    BoxEntityRenderer::BoxEntityRenderer() : EntityFunction(RENDERER_CUBE_FUNCTION)
    {
    }

    BoxEntityRenderer::~BoxEntityRenderer()
    {
    }

    void BoxEntityRenderer::Before(TimeStep time_step, std::shared_ptr<EntityInstance> renderer_inst)
    {
        // Replace with Hannis code
    }

    void BoxEntityRenderer::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> renderer_inst, std::shared_ptr<EntityInstance> particle_inst)
    {
        // Replace with Hannis code
    }

    void BoxEntityRenderer::After(TimeStep time_step, std::shared_ptr<EntityInstance> renderer_inst)
    {
        // Replace with Hannis code
    }

}
}
}
