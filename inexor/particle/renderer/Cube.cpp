/*
 * Cube.cpp
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#include "Cube.hpp"
#include "inexor/fpsgame/game.hpp"
#include "inexor/engine/engine.hpp"

namespace inexor {
namespace entity {
namespace particle {

    Cube::Cube() : EntityFunction(RENDERER_CUBE_FUNCTION)
    {
    }

    Cube::~Cube()
    {
    }

    void Cube::Before(TimeStep time_step, std::shared_ptr<EntityInstance> renderer_inst)
    {
        glPushMatrix();
        //rectshader->set();
        glDisable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glColor4f(0.1f, 1.0f, 0.9f, 0.2f);
        glBegin(GL_QUADS);
    }

    void Cube::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> renderer_inst, std::shared_ptr<EntityInstance> particle_inst)
    {
        vec pmin((*particle_inst)[POS]->vec3Val);
        vec pmax(pmin);
        float size = (*renderer_inst)[SIZE]->floatVal * (*particle_inst)[DENSITY]->floatVal / 2.0f;
        pmin.sub(size);
        pmax.add(size);
        // FRONT
        glVertex3d(pmin.x, pmin.y, pmin.z);
        glVertex3d(pmax.x, pmin.y, pmin.z);
        glVertex3d(pmax.x, pmax.y, pmin.z);
        glVertex3d(pmin.x, pmax.y, pmin.z);
        // BACK
        glVertex3d(pmax.x, pmax.y, pmax.z);
        glVertex3d(pmin.x, pmax.y, pmax.z);
        glVertex3d(pmin.x, pmin.y, pmax.z);
        glVertex3d(pmax.x, pmin.y, pmax.z);
        // RIGHT
        glVertex3d(pmax.x, pmax.y, pmax.z);
        glVertex3d(pmax.x, pmax.y, pmin.z);
        glVertex3d(pmax.x, pmin.y, pmin.z);
        glVertex3d(pmax.x, pmin.y, pmax.z);
        // LEFT
        glVertex3d(pmin.x, pmin.y, pmin.z);
        glVertex3d(pmin.x, pmax.y, pmin.z);
        glVertex3d(pmin.x, pmax.y, pmax.z);
        glVertex3d(pmin.x, pmin.y, pmax.z);
        // TOP
        glVertex3d(pmax.x, pmax.y, pmax.z);
        glVertex3d(pmin.x, pmax.y, pmax.z);
        glVertex3d(pmin.x, pmax.y, pmin.z);
        glVertex3d(pmax.x, pmax.y, pmin.z);
        // BOTTOM
        glVertex3d(pmin.x, pmin.y, pmin.z);
        glVertex3d(pmin.x, pmin.y, pmax.z);
        glVertex3d(pmax.x, pmin.y, pmax.z);
        glVertex3d(pmax.x, pmin.y, pmin.z);
    }

    void Cube::After(TimeStep time_step, std::shared_ptr<EntityInstance> renderer_inst)
    {
        glEnd();
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_CULL_FACE);
        glPopMatrix();
    }

}
}
}
