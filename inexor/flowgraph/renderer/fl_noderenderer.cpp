#include "inexor/engine/engine.h"
#include <vector>
#include "inexor/geom/curves/curvebase.h"
#include "inexor/geom/geom.h"
#include "inexor/flowgraph/renderer/fl_noderenderer.h"

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
        if(orient==index) 
        {
            // if this side of the box is selected, render the side in another color
            gle::color(vec::hexcolor(VSCRIPT_COLOR_SELECTION));
        }
        else
        {
            // hightlight node during execution
            if(SDL_GetTicks() - node->last_time < INEXOR_VSCRIPT_ACTIVE_NODE_TIMER_INTERVAL) node->box_color = VSCRIPT_COLOR_TRIGGERED;
            else node->box_color = node->default_box_color;
            gle::color(vec::hexcolor(node->box_color));
        }
    }


    void CVisualScriptRenderer::renderbox(CScriptNode* node, int orient)
    {
        /// I believe there is no better way to render a box using quads.
        /// You either write the box generator code directly or you let it generate.
        /// If you take a look at the original Sauer code you will see that generating
        /// the box using iterations is way more complicated to understand.

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


    void CVisualScriptSystem::render_node_relations()
    {
        if(!nodes.size()) return;

        for(unsigned int i=0; i<nodes.size(); i++)
        {   
            for(unsigned int e = 0; e < nodes[i]->children.size(); e++)
            {
                /// Please note: we will add the beginning point,
                /// 2 more interpolated points and the end point as
                /// parameter points for the bezier curve
                inexor::geom::CBezierCurve curve;
                curve.ClearAllPoints();
            
                /// create additional interpolation data
                vec t = nodes[i]->position;
                vec n = nodes[i]->children[e]->position;
                vec interpol1 = vec( (t.x+n.x)/2.0f, (t.y+n.y)/2.0f, (t.z+n.z)/2.0f - 30.0f);
                vec interpol2 = vec( (t.x+n.x)/2.0f, (t.y+n.y)/2.0f, (t.z+n.z)/2.0f + 30.0f);
            
                /// correct offset
                t.x += boxsize/2;
                t.y += boxsize/2;
                n.x += boxsize/2;
                n.y += boxsize/2;
                n.z += boxsize;

                curve.AddParameterPoint(t);
                curve.AddParameterPoint(interpol1);
                curve.AddParameterPoint(interpol2);
                curve.AddParameterPoint(n);

                curve.ComputeCache();

                glBegin(GL_LINES);
                gle::color(vec::hexcolor(VSCRIPT_COLOR_TRIGGERED));
                glLineWidth(10.0f);

                for(unsigned int h=0; h<curve.GetCachedPointsNumber() -1; h++)
                {
                    inexor::geom::SCustomOutputPoint t = curve.GetPoint_ByIndex(h);
                    inexor::geom::SCustomOutputPoint n = curve.GetPoint_ByIndex(h  +1);
                    glVertex3f(t.pos.x, t.pos.y, t.pos.z);
                    glVertex3f(n.pos.x, n.pos.y, n.pos.z);
                }
                glLineWidth(1.0f);
                glEnd();
            }
        }
    }


    void CVisualScriptSystem::render_nodes()
    {
        hovered_node = nullptr;

        unique_execution_pass_timestamp = SDL_GetTicks();

        for(unsigned int i=0; i<nodes.size(); i++) 
        {
            float dist = 0.0f;
            int orient = VSCRIPT_BOX_NO_INTERSECTION;
            vec p = nodes[i]->position;

            /// check ray/box intersection
            rayboxintersect(p, vec(boxsize), camera1->o, camdir, dist, orient);

            /// this node is selected
            nodes[i]->selected = (orient != VSCRIPT_BOX_NO_INTERSECTION);

            /// render a 200ms long color effect once its activated
            if( (nodes[i]->this_time - nodes[i]->last_time)  < INEXOR_VSCRIPT_ACTIVE_NODE_TIMER_INTERVAL) nodes[i]->box_color = VSCRIPT_COLOR_TRIGGERED;
            else nodes[i]->box_color = nodes[i]->default_box_color;

            if(NODE_TYPE_TIMER != nodes[i]->type) nodes[i]->this_time = unique_execution_pass_timestamp;

            renderbox(nodes[i], orient);

            if(!selection_blocked_by_geometry)
            {
                /// no matter where the box is being selected, render help lines
                if(orient != VSCRIPT_BOX_NO_INTERSECTION) 
                {
                    gle::color(vec::hexcolor(VSCRIPT_COLOR_GRAY));
                    renderboxhelplines(p);
                }
            }
            gle::color(vec::hexcolor(VSCRIPT_COLOR_BLACK));
            renderboxoutline(p);

            /// render white text above
            p.add(vec(boxsize/2));
            p.add(vec(0,0,4));
            particle_text(p + vec(0,0,1.0f), nodes[i]->node_name.c_str(), PART_TEXT, 1, 0xFFFFFF, 1.0f);
            particle_text(p, nodes[i]->node_comment.c_str(), PART_TEXT, 1, 0xFFFFFF, 1.0f);
        }

        /// which node is selected?
        for(unsigned int i=0; i<nodes.size(); i++)
            if(nodes[i]->selected && nullptr != nodes[i]) hovered_node = nodes[i];
    }


    void CVisualScriptSystem::render_debug_rays()
    {
        glBegin(GL_LINES);
        gle::color(vec::hexcolor(VSCRIPT_COLOR_TRIGGERED));
        glLineWidth(10.0f);

        for(unsigned int h=0; h<rays.size(); h++)
        {
            glVertex3f(rays[h].pos.x,rays[h].pos.y,rays[h].pos.z);
            glVertex3f(rays[h].target.x,rays[h].target.y,rays[h].target.z);
        }

        glLineWidth(1.0f);
        glEnd();
    }

};
};
