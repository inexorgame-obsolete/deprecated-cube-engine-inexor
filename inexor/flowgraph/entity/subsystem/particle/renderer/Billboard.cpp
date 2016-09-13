/*
 * Billboard.cpp
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#include "Billboard.h"
#include "inexor/fpsgame/game.hpp"

namespace inexor {
namespace entity {
namespace particle {

Billboard::Billboard() : EntityFunction(RENDERER_BILLBOARD_FUNCTION)
{
    shader = lookupshaderbyname("particlepoints");
    tex = NULL;
}

Billboard::~Billboard()
{
}

void Billboard::Before(TimeStep time_step, EntityInstance* renderer_inst)
{
    glPushMatrix();
    glShadeModel(GL_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDepthMask(GL_FALSE);
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    // logoutf("shader: %s texture: %s size: %2.2f", (*renderer_inst)[SHADER]->stringVal.c_str(), (*renderer_inst)[TEXTURE]->stringVal.c_str(), (*renderer_inst)[SIZE]->floatVal);
    if (!shader)
        shader = lookupshaderbyname("particlepoints"); // (*renderer_inst)[SHADER]->stringVal.c_str()
    if(shader)
    {
        shader->set();
        glUniform1f_(glGetUniformLocation_(shader->program, "pointSize"), (*renderer_inst)[SIZE]->floatVal);

        glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
        glEnable(GL_TEXTURE_2D);
        tex = textureload((*renderer_inst)[TEXTURE]->stringVal.c_str(), 0);
        glBindTexture(GL_TEXTURE_2D, tex->id);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glBegin(GL_POINTS);
    // TODO: get particle color
    glColor4f(1.0f, 0.5f, 0.5f, 0.5f);
}

void Billboard::Execute(TimeStep time_step, EntityInstance* renderer_inst, EntityInstance* particle_inst)
{
    glVertex3f((*particle_inst)[POS]->vec3Val.x, (*particle_inst)[POS]->vec3Val.y, (*particle_inst)[POS]->vec3Val.z);
}

void Billboard::After(TimeStep time_step, EntityInstance* renderer_inst)
{
    glEnd();
    glDisable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    if (shader)
    {
        glDisable(GL_POINT_SPRITE);
        glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
        glDisable(GL_TEXTURE_2D);
    }
    glDepthMask(GL_TRUE);
    glPopMatrix();
}

}
}
}
