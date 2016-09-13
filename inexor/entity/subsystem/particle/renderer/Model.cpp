/*
 * Model.cpp
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#include "Model.hpp"
#include "inexor/fpsgame/game.hpp"
#include "inexor/engine/engine.hpp"

namespace inexor {
namespace entity {
namespace particle {

Model::Model() : EntityFunction(RENDERER_MODEL_FUNCTION)
{
    m = NULL;
    yaw = 0.0f;
    pitch = 0.0f;
    offset = vec(0.0f, 0.0f, 0.0f);
}

Model::~Model()
{
}

void Model::Before(TimeStep time_step, EntityInstance* renderer_inst)
{
    model_name = (*renderer_inst)[MODEL]->stringVal;
    offset = (*renderer_inst)[OFFSET]->vec3Val;
    /*if (!m) {
        m = loadmodel(model_name.c_str());
    }*/
    glPushMatrix();
    //defaultshader->set();
    glDepthMask(false);
}

void Model::Execute(TimeStep time_step, EntityInstance* renderer_inst, EntityInstance* particle_inst)
{
    //if (m)
    //{
        vec v((*particle_inst)[VELOCITY]->vec3Val);
        vectoyawpitch(v, yaw, pitch);
        yaw += 90;
        vec o((*particle_inst)[POS]->vec3Val);
        o.add(offset);
        rendermodel(NULL, model_name.c_str(), ANIM_MAPMODEL|ANIM_LOOP, o, yaw, -((*particle_inst)[ROLL]->floatVal), MDL_CULL_VFC|MDL_CULL_OCCLUDED|MDL_LIGHT|MDL_LIGHT_FAST|MDL_DYNSHADOW, NULL, NULL, 0);
        //}
}

void Model::After(TimeStep time_step, EntityInstance* renderer_inst)
{
    glDepthMask(true);
    glPopMatrix();
    // m = NULL;
}

}
}
}
