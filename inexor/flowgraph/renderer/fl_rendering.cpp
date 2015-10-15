#include "inexor/flowgraph/node/fl_nodebase.h"
#include "inexor/flowgraph/renderer/fl_rendering.h"

namespace inexor {
namespace vscript {


CVisualScriptRenderer::CVisualScriptRenderer()
{
}

CVisualScriptRenderer::~CVisualScriptRenderer()
{
}

void CVisualScriptRenderer::adjust_selection_color(int orient, int index, int std_color_of_this_node)
{
    /// if this side of the box is selected, use a spicy orange color
    /// otherwise use a light blue color
    if(orient==index) 
    {
        gle::color(vec::hexcolor(0xFF5900));
        //if(selected) gle::color(vec::hexcolor(0xFF5900));
        //else gle::color(vec::hexcolor(0xFF9000));
    }
    else gle::color(vec::hexcolor(std_color_of_this_node));
}


void CVisualScriptRenderer::renderbox(vec p, int orient, int std_color_of_this_node)
{
    /// lets avoid macros here
    const float b = boxsize;

    glBegin(GL_QUADS);

    /// top
    adjust_selection_color(orient, VSCRIPT_BOX_TOP, std_color_of_this_node);
    glVertex3f(p.x,p.y,p.z+b);
    glVertex3f(p.x+b,p.y,p.z+b);
    glVertex3f(p.x+b,p.y+b,p.z+b);
    glVertex3f(p.x,p.y+b,p.z+b);

    /// bottom
    adjust_selection_color(orient, VSCRIPT_BOX_BOTTOM, std_color_of_this_node);
    glVertex3f(p.x,p.y+b,p.z);
    glVertex3f(p.x+b,p.y+b,p.z);
    glVertex3f(p.x+b,p.y,p.z);
    glVertex3f(p.x,p.y,p.z);

    /// front
    adjust_selection_color(orient, VSCRIPT_BOX_FRONT, std_color_of_this_node);
    glVertex3f(p.x,p.y,p.z);
    glVertex3f(p.x+b,p.y,p.z);
    glVertex3f(p.x+b,p.y,p.z+b);
    glVertex3f(p.x,p.y,p.z+b);

    /// back
    adjust_selection_color(orient, VSCRIPT_BOX_BACK, std_color_of_this_node);
    glVertex3f(p.x,p.y+b,p.z+b);
    glVertex3f(p.x+b,p.y+b,p.z+b);
    glVertex3f(p.x+b,p.y+b,p.z);
    glVertex3f(p.x,p.y+b,p.z);

    /// left
    adjust_selection_color(orient, VSCRIPT_BOX_LEFT, std_color_of_this_node);
    glVertex3f(p.x,p.y,p.z+b);
    glVertex3f(p.x,p.y+b,p.z+b);
    glVertex3f(p.x,p.y+b,p.z);
    glVertex3f(p.x,p.y,p.z);

    /// right
    adjust_selection_color(orient, VSCRIPT_BOX_RIGHT, std_color_of_this_node);
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


void renderboxhelplines(vec p)
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
