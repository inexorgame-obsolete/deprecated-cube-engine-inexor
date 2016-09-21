/*
 * Origin.cpp
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#include "Origin.hpp"
#include "inexor/fpsgame/game.hpp"
#include "inexor/engine/engine.hpp"

namespace inexor {
namespace entity {
namespace particle {

    Origin::Origin() : EntityFunction(RENDERER_ORIGIN_FUNCTION)
    {
        emitted_by = entity_system->GetRelationshipTypeManager()->Get(REL_EMITTED_BY);
    }

    Origin::~Origin()
    {
    }

    void Origin::Before(TimeStep time_step, std::shared_ptr<EntityInstance> renderer_inst)
    {
        glPushMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //lineshader->set();
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);
        glColor4f(1.0f, 0.8f, 0.6f, 0.4f);
        glLineStipple(1, 0x0C0F);
        glEnable(GL_LINE_STIPPLE);
        glBegin(GL_LINES);
    }

    void Origin::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> renderer_inst, std::shared_ptr<EntityInstance> particle_inst)
    {
        vec p_particle((*particle_inst)[POS]->vec3Val);
        vec p_emitter(particle_inst->outgoing[emitted_by->uuid].front()->endNode[POS]->vec3Val);
        glVertex3f(p_particle.x, p_particle.y, p_particle.z);
        glVertex3f(p_emitter.x, p_emitter.y, p_emitter.z);
    }

    void Origin::After(TimeStep time_step, std::shared_ptr<EntityInstance> renderer_inst)
    {
        glEnd();
        glDisable(GL_LINE_STIPPLE);
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
        glPopMatrix();
    }

}
}
}
