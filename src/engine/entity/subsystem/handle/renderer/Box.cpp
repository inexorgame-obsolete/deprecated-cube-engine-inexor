/*
 * Box.cpp
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#include "Box.h"
#include "fpsgame/game.h"
#include "engine.h"

namespace inexor {
namespace entity {
namespace handle {

Box::Box() : EntityFunction(FUNC_BOX_HANDLE_RENDERER)
{
}

Box::~Box()
{
}

void Box::Before(TimeStep time_step, EntityInstance* handle_renderer)
{
    (*handle_renderer)[HOVERED] = false;
    (*handle_renderer)[DIST] = 0.0f;
    glPushMatrix();
    lineshader->set();
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(4.0f);
    glBegin(GL_QUADS);
}

void Box::Execute(TimeStep time_step, RelationshipInstance* renders_handle)
{
    vec pos(renders_handle->endNode[POS]->vec3Val);
    vec dim(renders_handle->endNode[DIM]->vec3Val);

    vec pmax(pos);
    pmax.add(dim);

    float dist = 0.0f;
    int orient = -1;
    bool intersect = rayboxintersect(pos, dim, camera1->o, camdir, dist, orient);
    // logoutf("camdir(%2.2f, %2.2f, %2.2f) pmin(%2.2f, %2.2f, %2.2f) pmax(%2.2f, %2.2f, %2.2f) dim(%2.2f, %2.2f, %2.2f)", camdir.x, camdir.y, camdir.z, pos.x, pos.y, pos.z, pmax.x, pmax.y, pmax.z, dim.x, dim.y, dim.z);
    if (intersect) {
        // logoutf("intersect camdir(%2.2f, %2.2f, %2.2f) pos(%2.2f, %2.2f, %2.2f) dist: %2.2f orient: %d", camdir.x, camdir.y, camdir.z, pos.x, pos.y, pos.z, dist, orient);
        renders_handle->endNode[HOVERED] = true;
        renders_handle->endNode[DIST] = dist;
    } else {
        renders_handle->endNode[HOVERED] = false;
        renders_handle->endNode[DIST] = 0.0f;
    }
    // Render box faces
    for (int i = 0; i < 6; i++)
    {
        if (i != orient)
        {
            RenderFace(pos, pmax, i, orient);
        }
    }
    // Render hovered face
    if (orient >= 0)
    {
        RenderFace(pos, pmax, orient, orient);
    }
}

void Box::After(TimeStep time_step, EntityInstance* handle_renderer)
{
    glEnd();
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glPopMatrix();
}

void Box::RenderFace(vec pos, vec pmax, int orient, int actual_orient)
{
    SetColor(orient, actual_orient);
    switch(orient)
    {
        case 0:
            glVertex3f(pos.x, pos.y, pos.z);
            glVertex3f(pos.x, pmax.y, pos.z);
            glVertex3f(pos.x, pmax.y, pmax.z);
            glVertex3f(pos.x, pos.y, pmax.z);
            break;
        case 1:
            glVertex3f(pmax.x, pmax.y, pmax.z);
            glVertex3f(pmax.x, pmax.y, pos.z);
            glVertex3f(pmax.x, pos.y, pos.z);
            glVertex3f(pmax.x, pos.y, pmax.z);
            break;
        case 2:
            glVertex3f(pos.x, pos.y, pos.z);
            glVertex3f(pos.x, pos.y, pmax.z);
            glVertex3f(pmax.x, pos.y, pmax.z);
            glVertex3f(pmax.x, pos.y, pos.z);
            break;
        case 3:
            glVertex3f(pmax.x, pmax.y, pmax.z);
            glVertex3f(pos.x, pmax.y, pmax.z);
            glVertex3f(pos.x, pmax.y, pos.z);
            glVertex3f(pmax.x, pmax.y, pos.z);
            break;
        case 4:
            glVertex3f(pos.x, pos.y, pos.z);
            glVertex3f(pmax.x, pos.y, pos.z);
            glVertex3f(pmax.x, pmax.y, pos.z);
            glVertex3f(pos.x, pmax.y, pos.z);
            break;
        case 5:
            glVertex3f(pmax.x, pmax.y, pmax.z);
            glVertex3f(pos.x, pmax.y, pmax.z);
            glVertex3f(pos.x, pos.y, pmax.z);
            glVertex3f(pmax.x, pos.y, pmax.z);
            break;
    }
}

void Box::SetColor(int orient, int actual_orient)
{
    if (actual_orient >= 0)
    {
        if (actual_orient == orient) {
            glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
        } else {
            // glColor4f(0.7f, 0.7f, 0.9f, 0.6f);
            glColor4f(0.5f, 0.5f, 0.9f, 0.5f);
        }

    } else {
        // glLineWidth(1.0f);
        glColor4f(0.5f, 0.5f, 0.9f, 0.5f);
    }
}

}
}
}
