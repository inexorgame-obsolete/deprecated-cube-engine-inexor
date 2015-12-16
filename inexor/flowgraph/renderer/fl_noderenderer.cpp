#include "inexor/flowgraph/renderer/fl_noderenderer.h"

namespace inexor {
namespace vscript {


    CNodeRenderer::CNodeRenderer()
    {
    }

    CNodeRenderer::~CNodeRenderer()
    {
    }



    void CNodeRenderer::adjust_selection_color(int orient, int index, CScriptNode* node)
    {
        // hightlight node during execution
        if(SDL_GetTicks() - node->last_time < INEXOR_VSCRIPT_ACTIVE_NODE_TIMER_INTERVAL) node->box_color = VSCRIPT_COLOR_TRIGGERED;
        else node->box_color = node->default_box_color;
        if(orient==index) 
        {
            // if this side of the box is selected, render the side in another color
            node->box_color = VSCRIPT_COLOR_SELECTION;
        }
        gle::color(vec::hexcolor(node->box_color));
    }


    void CNodeRenderer::render_box(CScriptNode* node, int orient)
    {
        /// I believe there is no better way to render a box using quads.
        /// You either write the box generator code directly or you let it generate.
        /// If you take a look at the original Sauer code you will see that generating
        /// the box using iterations is way more complicated to understand.

        const float b = boxsize;
        vec p = node->pos;

        glBegin(GL_QUADS);
        
        adjust_selection_color(orient, VSCRIPT_BOX_TOP, node);
        glVertex3f(p.x,p.y,p.z+b);
        glVertex3f(p.x+b,p.y,p.z+b);
        glVertex3f(p.x+b,p.y+b,p.z+b);
        glVertex3f(p.x,p.y+b,p.z+b);

        adjust_selection_color(orient, VSCRIPT_BOX_BOTTOM, node);
        glVertex3f(p.x,p.y+b,p.z);
        glVertex3f(p.x+b,p.y+b,p.z);
        glVertex3f(p.x+b,p.y,p.z);
        glVertex3f(p.x,p.y,p.z);

        adjust_selection_color(orient, VSCRIPT_BOX_FRONT, node);
        glVertex3f(p.x,p.y,p.z);
        glVertex3f(p.x+b,p.y,p.z);
        glVertex3f(p.x+b,p.y,p.z+b);
        glVertex3f(p.x,p.y,p.z+b);

        adjust_selection_color(orient, VSCRIPT_BOX_BACK, node);
        glVertex3f(p.x,p.y+b,p.z+b);
        glVertex3f(p.x+b,p.y+b,p.z+b);
        glVertex3f(p.x+b,p.y+b,p.z);
        glVertex3f(p.x,p.y+b,p.z);

        adjust_selection_color(orient, VSCRIPT_BOX_LEFT, node);
        glVertex3f(p.x,p.y,p.z+b);
        glVertex3f(p.x,p.y+b,p.z+b);
        glVertex3f(p.x,p.y+b,p.z);
        glVertex3f(p.x,p.y,p.z);

        adjust_selection_color(orient, VSCRIPT_BOX_RIGHT, node);
        glVertex3f(p.x+b,p.y,p.z);
        glVertex3f(p.x+b,p.y+b,p.z);
        glVertex3f(p.x+b,p.y+b,p.z+b);
        glVertex3f(p.x+b,p.y,p.z+b);
        glEnd();
    }


    void CNodeRenderer::render_box_outline(vec p)
    {
        const float b = boxsize;

        glBegin(GL_LINE_LOOP);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex3f(p.x,p.y,p.z+b);
        glVertex3f(p.x+b,p.y,p.z+b);
        glVertex3f(p.x+b,p.y+b,p.z+b);
        glVertex3f(p.x,p.y+b,p.z+b);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex3f(p.x,p.y,p.z);
        glVertex3f(p.x+b,p.y,p.z);
        glVertex3f(p.x+b,p.y+b,p.z);
        glVertex3f(p.x,p.y+b,p.z);
        glEnd();

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


    void CNodeRenderer::render_box_helplines(vec p)
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
