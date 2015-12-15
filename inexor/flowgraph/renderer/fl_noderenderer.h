/// @file fl_rendering.h
/// @author Johannes Schneider
/// @brief Renderer for nodes and node relations

#ifndef INEXOR_VSCRIPT_NODE_RENDERER_HEADER
#define INEXOR_VSCRIPT_NODE_RENDERER_HEADER

#include <vector>

#include "inexor/flowgraph/debugger/fl_dbgrays.h"
#include "inexor/flowgraph/node/fl_nodebase.h"
#include "inexor/flowgraph/timer/fl_timer.h"


namespace inexor {
namespace vscript {

    extern const float boxsize;

    enum VSCRIPT_ENTITY_BOX_ORIENTATION
    {
        VSCRIPT_BOX_NO_INTERSECTION = -1,
        VSCRIPT_BOX_LEFT,
        VSCRIPT_BOX_RIGHT,
        VSCRIPT_BOX_FRONT,
        VSCRIPT_BOX_BACK,
        VSCRIPT_BOX_BOTTOM,
        VSCRIPT_BOX_TOP
    };


    class CVisualScriptRenderer
    {

        public:

            std::vector<CDebugRay> rays;


            CVisualScriptRenderer()
            {
            }


            ~CVisualScriptRenderer()
            {
            }


            void start_rendering()
            {
                notextureshader->set();
                gle::enablevertex();
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                enablepolygonoffset(GL_POLYGON_OFFSET_LINE);
            }


            void end_rendering()
            {
                disablepolygonoffset(GL_POLYGON_OFFSET_LINE);
                gle::clearvbo();
                gle::clearebo();
                gle::disablevertex();
            }


            void adjust_selection_color(int orient, int index, CScriptNode* node)
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


            void renderbox(CScriptNode* node, int orient)
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


            void renderboxoutline(vec p)
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


            void render_debug_rays()
            {
                glBegin(GL_LINES);
                gle::color(vec::hexcolor(VSCRIPT_COLOR_DEBUG_RAY));
                glLineWidth(10.0f);

                /*
                for(unsigned int h=0; h<rays.size(); h++)
                {
                    glVertex3f(rays[h].pos.x,rays[h].pos.y,rays[h].pos.z);
                    glVertex3f(rays[h].target.x,rays[h].target.y,rays[h].target.z);
                }
                */
                glLineWidth(1.0f);
                glEnd();
            }
    };

};
};

#endif
