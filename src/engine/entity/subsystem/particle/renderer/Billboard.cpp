/*
 * Billboard.cpp
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#include "Billboard.h"
#include "fpsgame/game.h"

/*
namespace game {
    extern fpsent *player1;
}
*/

namespace inexor {
namespace entity {
namespace particle {

Billboard::Billboard() : EntityFunction(RENDERER_BILLBOARD_FUNCTION)
{
}

Billboard::~Billboard()
{
}

void Billboard::Before(TimeStep time_step, EntityInstance* renderer_inst)
{
    glPushMatrix();
    // glShadeModel(GL_SMOOTH);
    // glEnable(GL_POINT_SMOOTH);
    // glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    defaultshader->set();
    // ... TODO get point size
    // if (pr_inst->attributes.count("size") == 1) pointSize = pr_inst->attributes["size"];
    // else pointSize = 1.0f;
    glDepthMask(GL_FALSE);
    // glEnable(GL_POINT_SPRITE);
    // glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    // if (!shader) shader = lookupshaderbyname("particlepoints");
    // if(!shader) return;
    // shader->set();
    // glUniform1f_(glGetUniformLocation_(shader->program, "pointSize"), pointSize);
    // glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
    // glEnable(GL_TEXTURE_2D);
    // tex = textureload(pr_inst->texture.c_str(), texclamp);
    // glBindTexture(GL_TEXTURE_2D, tex->id);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize(5.0f);
    glBegin(GL_POINTS);
    // TODO: get particle color
    glColor4f(1.0f, 0.5f, 0.5f, 0.5f);
}

void Billboard::Execute(TimeStep time_step, EntityInstance* renderer_inst, EntityInstance* particle_inst)
{
    glVertex3f((*particle_inst)[POS]->vec3Val.x, (*particle_inst)[POS]->vec3Val.y, (*particle_inst)[POS]->vec3Val.z);
    logoutf(
        "( %2.2f, %2.2f, %2.2f )  ( %2.2f, %2.2f, %2.2f )",
        (*particle_inst)[POS]->vec3Val.x, (*particle_inst)[POS]->vec3Val.y, (*particle_inst)[POS]->vec3Val.z,
        game::player1->o.x, game::player1->o.y, game::player1->o.z
    );
}

void Billboard::After(TimeStep time_step, EntityInstance* renderer_inst)
{
    glEnd();
    glDisable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glDisable(GL_POINT_SPRITE);
    // glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
    // glDisable(GL_TEXTURE_2D);
    glDepthMask(GL_TRUE);
    glPopMatrix();
}

}
}
}
