/*
 * Origin.cpp
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#include "Origin.h"
#include "fpsgame/game.h"
#include "engine.h"

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

void Origin::Before(TimeStep time_step, EntityInstance* renderer_inst)
{
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    defaultshader->set();
    glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4f);
    glBegin(GL_LINES);
}

void Origin::Execute(TimeStep time_step, EntityInstance* renderer_inst, EntityInstance* particle_inst)
{
    vec p_particle((*particle_inst)[POS]->vec3Val);
    vec p_emitter(particle_inst->outgoing[emitted_by].front()->endNode[POS]->vec3Val);
    glVertex3f(p_particle.x, p_particle.y, p_particle.z);
    glVertex3f(p_emitter.x, p_emitter.y, p_emitter.z);
}

void Origin::After(TimeStep time_step, EntityInstance* renderer_inst)
{
    glEnd();
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

}
}
}
