#include "inexor/flowgraph/render/fl_render.hpp"

namespace inexor {
namespace vscript {

    CNodeRenderer::CNodeRenderer()
    {
        triggered_color = INEXOR_VSCRIPT_COLOR_TRIGGERED;
    }

    CNodeRenderer::~CNodeRenderer()
    {
    }


    void CNodeRenderer::adjust_selection_color(int orient, int index)
    {
        INEXOR_VSCRIPT_NODE_COLORS temp_color = box_color;
        if(orient == index) 
        {
            temp_color = INEXOR_VSCRIPT_COLOR_SELECTION;
        }
        gle::color(vec::hexcolor(temp_color));
    }

    void CNodeRenderer::render_box(vec p, int orient)
    {
        /// There is probably no better way to render a box than to use quads.
        /// You either write the box generator code directly or you let it generate.
        /// If you take a look at the original Sauer code you will see that generating
        /// the box using iterations is way more complicated to understand.
        glBegin(GL_QUADS);

        adjust_selection_color(orient, INEXOR_VSCRIPT_BOX_TOP);
        glVertex3f(p.x,p.y,p.z+boxsize);
        glVertex3f(p.x+boxsize,p.y,p.z+boxsize);
        glVertex3f(p.x+boxsize,p.y+boxsize,p.z+boxsize);
        glVertex3f(p.x,p.y+boxsize,p.z+boxsize);

        adjust_selection_color(orient, INEXOR_VSCRIPT_BOX_BOTTOM);
        glVertex3f(p.x,p.y+boxsize,p.z);
        glVertex3f(p.x+boxsize,p.y+boxsize,p.z);
        glVertex3f(p.x+boxsize,p.y,p.z);
        glVertex3f(p.x,p.y,p.z);

        adjust_selection_color(orient, INEXOR_VSCRIPT_BOX_FRONT);
        glVertex3f(p.x,p.y,p.z);
        glVertex3f(p.x+boxsize,p.y,p.z);
        glVertex3f(p.x+boxsize,p.y,p.z+boxsize);
        glVertex3f(p.x,p.y,p.z+boxsize);

        adjust_selection_color(orient, INEXOR_VSCRIPT_BOX_BACK);
        glVertex3f(p.x,p.y+boxsize,p.z+boxsize);
        glVertex3f(p.x+boxsize,p.y+boxsize,p.z+boxsize);
        glVertex3f(p.x+boxsize,p.y+boxsize,p.z);
        glVertex3f(p.x,p.y+boxsize,p.z);

        adjust_selection_color(orient, INEXOR_VSCRIPT_BOX_LEFT);
        glVertex3f(p.x,p.y,p.z+boxsize);
        glVertex3f(p.x,p.y+boxsize,p.z+boxsize);
        glVertex3f(p.x,p.y+boxsize,p.z);
        glVertex3f(p.x,p.y,p.z);

        adjust_selection_color(orient, INEXOR_VSCRIPT_BOX_RIGHT);
        glVertex3f(p.x+boxsize,p.y,p.z);
        glVertex3f(p.x+boxsize,p.y+boxsize,p.z);
        glVertex3f(p.x+boxsize,p.y+boxsize,p.z+boxsize);
        glVertex3f(p.x+boxsize,p.y,p.z+boxsize);

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

        /// render help line for X AXIS
        glVertex3f(p.x,p.y,p.z);
        glVertex3f(p.x-helpline_distance,p.y,p.z);
        glVertex3f(p.x+boxsize,p.y,p.z);
        glVertex3f(p.x+boxsize+helpline_distance,p.y,p.z);

        glVertex3f(p.x,p.y+boxsize,p.z);
        glVertex3f(p.x-helpline_distance,p.y+boxsize,p.z);
        glVertex3f(p.x+boxsize,p.y+boxsize,p.z);
        glVertex3f(p.x+boxsize+helpline_distance,p.y+boxsize,p.z);

        glVertex3f(p.x,p.y,p.z+boxsize);
        glVertex3f(p.x-helpline_distance,p.y,p.z+boxsize);
        glVertex3f(p.x+boxsize,p.y,p.z+boxsize);
        glVertex3f(p.x+boxsize+helpline_distance,p.y,p.z+boxsize);

        glVertex3f(p.x,p.y+boxsize,p.z+boxsize);
        glVertex3f(p.x-helpline_distance,p.y+boxsize,p.z+boxsize);
        glVertex3f(p.x+boxsize,p.y+boxsize,p.z+boxsize);
        glVertex3f(p.x+boxsize+helpline_distance,p.y+boxsize,p.z+boxsize);


        /// render help line for Y AXIS
        glVertex3f(p.x,p.y,p.z);
        glVertex3f(p.x,p.y-helpline_distance,p.z);
        glVertex3f(p.x,p.y+boxsize,p.z);
        glVertex3f(p.x,p.y+boxsize+helpline_distance,p.z);

        glVertex3f(p.x+boxsize,p.y,p.z);
        glVertex3f(p.x+boxsize,p.y-helpline_distance,p.z);
        glVertex3f(p.x+boxsize,p.y+boxsize,p.z);
        glVertex3f(p.x+boxsize,p.y+boxsize+helpline_distance,p.z);

        glVertex3f(p.x,p.y,p.z+boxsize);
        glVertex3f(p.x,p.y-helpline_distance,p.z+boxsize);
        glVertex3f(p.x,p.y+boxsize,p.z+boxsize);
        glVertex3f(p.x,p.y+boxsize+helpline_distance,p.z+boxsize);

        glVertex3f(p.x+boxsize,p.y,p.z+boxsize);
        glVertex3f(p.x+boxsize,p.y-helpline_distance,p.z+boxsize);
        glVertex3f(p.x+boxsize,p.y+boxsize,p.z+boxsize);
        glVertex3f(p.x+boxsize,p.y+boxsize+helpline_distance,p.z+boxsize);


        /// render help line for Y AXIS
        glVertex3f(p.x,p.y,p.z);
        glVertex3f(p.x,p.y,p.z-helpline_distance);
        glVertex3f(p.x,p.y,p.z+boxsize);
        glVertex3f(p.x,p.y,p.z+boxsize+helpline_distance);

        glVertex3f(p.x,p.y+boxsize,p.z);
        glVertex3f(p.x,p.y+boxsize,p.z-helpline_distance);
        glVertex3f(p.x,p.y+boxsize,p.z+boxsize);
        glVertex3f(p.x,p.y+boxsize,p.z+boxsize+helpline_distance);

        glVertex3f(p.x+boxsize,p.y,p.z);
        glVertex3f(p.x+boxsize,p.y,p.z-helpline_distance);
        glVertex3f(p.x+boxsize,p.y,p.z+boxsize);
        glVertex3f(p.x+boxsize,p.y,p.z+boxsize+helpline_distance);

        glVertex3f(p.x+boxsize,p.y+boxsize,p.z);
        glVertex3f(p.x+boxsize,p.y+boxsize,p.z-helpline_distance);
        glVertex3f(p.x+boxsize,p.y+boxsize,p.z+boxsize);
        glVertex3f(p.x+boxsize,p.y+boxsize,p.z+boxsize+helpline_distance);
        
        glEnd();
    }

};
};
