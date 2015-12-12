#include "inexor/engine/engine.h"
#include <vector>
#include "inexor/flowgraph/renderer/fl_rendering.h"

namespace inexor {
namespace vscript {


    CVisualScriptRenderer::CVisualScriptRenderer()
    {
    }


    CVisualScriptRenderer::~CVisualScriptRenderer()
    {
    }



    void CVisualScriptRenderer::start_rendering()
    {
        notextureshader->set();
        gle::enablevertex();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        enablepolygonoffset(GL_POLYGON_OFFSET_LINE);
    }


    void CVisualScriptRenderer::end_rendering()
    {
        disablepolygonoffset(GL_POLYGON_OFFSET_LINE);
        gle::clearvbo();
        gle::clearebo();
        gle::disablevertex();
    }


    void CVisualScriptRenderer::adjust_selection_color(int orient, int index, CScriptNode* node)
    {
        /// if this side of the box is selected, use a spicy orange color
        /// otherwise use a light blue color
        if(orient==index) 
        {
            gle::color(vec::hexcolor(0xFF5900));
            //if(selected) gle::color(vec::hexcolor(0xFF5900));
            //else gle::color(vec::hexcolor(0xFF9000));
        }
        else
        {
            if(SDL_GetTicks() - node->last_time < INEXOR_VSCRIPT_ACTIVE_NODE_TIMER_INTERVAL) node->box_color = VSCRIPT_COLOR_TRIGGERED;
            else node->box_color = node->default_box_color;
            gle::color(vec::hexcolor(node->box_color));
        }
    }


    void CVisualScriptRenderer::renderbox(CScriptNode* node, int orient)
    {
        const float b = boxsize;
        vec p = node->position;

        glBegin(GL_QUADS);

        /// top
        adjust_selection_color(orient, VSCRIPT_BOX_TOP, node);
        glVertex3f(p.x,p.y,p.z+b);
        glVertex3f(p.x+b,p.y,p.z+b);
        glVertex3f(p.x+b,p.y+b,p.z+b);
        glVertex3f(p.x,p.y+b,p.z+b);

        /// bottom
        adjust_selection_color(orient, VSCRIPT_BOX_BOTTOM, node);
        glVertex3f(p.x,p.y+b,p.z);
        glVertex3f(p.x+b,p.y+b,p.z);
        glVertex3f(p.x+b,p.y,p.z);
        glVertex3f(p.x,p.y,p.z);

        /// front
        adjust_selection_color(orient, VSCRIPT_BOX_FRONT, node);
        glVertex3f(p.x,p.y,p.z);
        glVertex3f(p.x+b,p.y,p.z);
        glVertex3f(p.x+b,p.y,p.z+b);
        glVertex3f(p.x,p.y,p.z+b);

        /// back
        adjust_selection_color(orient, VSCRIPT_BOX_BACK, node);
        glVertex3f(p.x,p.y+b,p.z+b);
        glVertex3f(p.x+b,p.y+b,p.z+b);
        glVertex3f(p.x+b,p.y+b,p.z);
        glVertex3f(p.x,p.y+b,p.z);

        /// left
        adjust_selection_color(orient, VSCRIPT_BOX_LEFT, node);
        glVertex3f(p.x,p.y,p.z+b);
        glVertex3f(p.x,p.y+b,p.z+b);
        glVertex3f(p.x,p.y+b,p.z);
        glVertex3f(p.x,p.y,p.z);

        /// right
        adjust_selection_color(orient, VSCRIPT_BOX_RIGHT, node);
        glVertex3f(p.x+b,p.y,p.z);
        glVertex3f(p.x+b,p.y+b,p.z);
        glVertex3f(p.x+b,p.y+b,p.z+b);
        glVertex3f(p.x+b,p.y,p.z+b);
        glEnd();
    }


    void CVisualScriptRenderer::renderboxoutline(vec p)
    {
        const float b = boxsize;

        /// render gray outline (TOP)
        glBegin(GL_LINE_LOOP);
    
        /// TODO: does this work?
        glDepthFunc(GL_LEQUAL);

        glColor3f(0.0f,0.0f,0.0f);
        glVertex3f(p.x,p.y,p.z+b);
        glVertex3f(p.x+b,p.y,p.z+b);
        glVertex3f(p.x+b,p.y+b,p.z+b);
        glVertex3f(p.x,p.y+b,p.z+b);
        glEnd();

        /// render gray outline (BOTTOM)
        glBegin(GL_LINE_LOOP);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex3f(p.x,p.y,p.z);
        glVertex3f(p.x+b,p.y,p.z);
        glVertex3f(p.x+b,p.y+b,p.z);
        glVertex3f(p.x,p.y+b,p.z);
        glEnd();

        /// render connection lines
        glBegin(GL_LINES);
        glVertex3f(p.x,p.y,p.z);
        glVertex3f(p.x,p.y,p.z+b);
        glVertex3f(p.x+b,p.y,p.z);
        glVertex3f(p.x+b,p.y,p.z+b);
        glVertex3f(p.x+b,p.y+b,p.z);
        glVertex3f(p.x+b,p.y+b,p.z+b);
        glVertex3f(p.x,p.y+b,p.z);
        glVertex3f(p.x,p.y+b,p.z+b);
        glEnd();
    }


    void CVisualScriptRenderer::renderboxhelplines(vec p)
    {
        glBegin(GL_LINES);

        /// we can't render to infinity, so lets just use a very big value
        const float helpline_distance = 1000.0f;
        const float b = boxsize;

        /// render help line for X AXIS
        glVertex3f(p.x-helpline_distance,p.y,p.z);
        glVertex3f(p.x+helpline_distance,p.y,p.z);
        glVertex3f(p.x-helpline_distance,p.y,p.z+b);
        glVertex3f(p.x+helpline_distance,p.y,p.z+b);
        glVertex3f(p.x-helpline_distance,p.y+b,p.z);
        glVertex3f(p.x+helpline_distance,p.y+b,p.z);
        glVertex3f(p.x-helpline_distance,p.y+b,p.z+b);
        glVertex3f(p.x+helpline_distance,p.y+b,p.z+b);

        /// render help line for Y AXIS
        glVertex3f(p.x,p.y-helpline_distance,p.z);
        glVertex3f(p.x,p.y+helpline_distance,p.z);
        glVertex3f(p.x+b,p.y-helpline_distance,p.z);
        glVertex3f(p.x+b,p.y+helpline_distance,p.z);
        glVertex3f(p.x,p.y-helpline_distance,p.z+b);
        glVertex3f(p.x,p.y+helpline_distance,p.z+b);
        glVertex3f(p.x+b,p.y-helpline_distance,p.z+b);
        glVertex3f(p.x+b,p.y+helpline_distance,p.z+b);

        /// render help line for Z AXIS
        glVertex3f(p.x,p.y,p.z-helpline_distance);
        glVertex3f(p.x,p.y,p.z+helpline_distance);
        glVertex3f(p.x+b,p.y,p.z-helpline_distance);
        glVertex3f(p.x+b,p.y,p.z+helpline_distance);
        glVertex3f(p.x,p.y+b,p.z-helpline_distance);
        glVertex3f(p.x,p.y+b,p.z+helpline_distance);
        glVertex3f(p.x+b,p.y+b,p.z-helpline_distance);
        glVertex3f(p.x+b,p.y+b,p.z+helpline_distance);    
        glEnd();
    }

};
};
