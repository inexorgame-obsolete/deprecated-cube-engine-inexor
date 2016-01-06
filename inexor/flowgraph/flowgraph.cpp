#include "inexor/flowgraph/flowgraph.h"
#include "inexor/fpsgame/game.hpp"
#include "inexor/flowgraph/sleep/fl_sleep.h"
#include "inexor/flowgraph/timer/fl_timer.h"
#include "inexor/flowgraph/comments/fl_comment.h"
#include "inexor/flowgraph/functions/fl_functionbase.h"
#include "inexor/flowgraph/functions/fl_functions.h"

#include "inexor/flowgraph/areas/block/fl_area_block.h"
#include "inexor/flowgraph/areas/sphere/fl_area_sphere.h"

#include "inexor/geom/geom.h"
#include "inexor/geom/curves/bezier/bezier.h"

extern selinfo sel, lastsel, savedsel;
extern bool editmode;
extern int gridsize;


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


namespace inexor {
namespace vscript {

    // create an instance
    CVisualScriptSystem vScript3D;


    CVisualScriptSystem::CVisualScriptSystem() 
    {
        selection_blocked_by_geometry = false;
    }


    CVisualScriptSystem::~CVisualScriptSystem() 
    {
        for(unsigned int i=0; i<nodes.size(); i++) delete (nodes[i]);
        nodes.clear();
    }


    CScriptNode* CVisualScriptSystem::add_node(VSCRIPT_NODE_TYPE type, int parameter_count, ...)
    {
        CScriptNode* created_node = nullptr;
        vec target = vec(sel.o.x,sel.o.y,sel.o.z);
        vec offset = vec(gridsize/2,gridsize/2,gridsize/2);
        target.add(offset);

        va_list parameters;
        std::vector<std::string> arguments;
        va_start(parameters, parameter_count);
        for(unsigned int i=0; i<parameter_count; i++)
        {
            arguments.push_back(va_arg(parameters, char *));
        }
        va_end(parameters);
    

        switch(type)
        {
            case NODE_TYPE_TIMER:
            {
                /// convert parameters form const string to unsigned int
                /// TODO: make sure those indices are correct!
                unsigned int interval   = atoi(arguments[0].c_str());
                unsigned int startdelay = atoi(arguments[1].c_str());
                unsigned int limit      = atoi(arguments[2].c_str());
                unsigned int cooldown   = atoi(arguments[3].c_str());
                const char* name        = arguments[4].c_str();
                const char* comment     = arguments[5].c_str();

                /// TODO: which timer format?
                INEXOR_VSCRIPT_TIME_FORMAT timer_format = TIME_FORMAT_MILISECONDS;
                
                /// Create a new timer and synchronise them!
                created_node = new CTimerNode(target, interval, startdelay, limit, cooldown, name, comment, timer_format);
                sync_all_timers();
                break;
            }

            case NODE_TYPE_COMMENT:
            {
                created_node = new CCommentNode(target, arguments[0].c_str(), arguments[1].c_str());
                break;
            }

            case NODE_TYPE_FUNCTION:
            {
                switch(atoi(arguments[0].c_str()))
                {
                    case FUNCTION_CONOUTF:
                        created_node = new CFunctionConoutfNode(target, arguments[1].c_str());
                        break;
                    case FUNCTION_PLAYSOUND:
                        created_node = new CFunctionPlaysoundNode(target, arguments[1].c_str());
                        break;
                }
                break;
            }

            case NODE_TYPE_SLEEP:
            {
                unsigned int wait_time   = atoi(arguments[0].c_str());
                created_node = new CSleepNode(target, wait_time); 
                break;
            }

            case NODE_TYPE_AREA_BLOCK:
            {
                vec end = target;
                end.add(vec(50,50,50));
                created_node = new CCubeAreaNode(target,end,arguments[0].c_str(),arguments[1].c_str());
                break;
            }

            case NODE_TYPE_AREA_SPHERE:
            {
                vec rad = target;
                rad.add(vec(20,20,20));
                created_node = new CSphereAreaNode(target,rad,arguments[0].c_str(),arguments[1].c_str());
                break;
            }

        }
        if(nullptr != created_node)  nodes.push_back(created_node);
        return created_node;
    }


    void CVisualScriptSystem::update_drag_n_drop()
    {
        if(nullptr != selected_node)
        {
            static float selected_dist = 0.0f;
            static bool calculated = false;
            if(!calculated)
            {
                selected_dist = selected_node->pos.dist(game::player1->o);
                calculated = true;
            }
            
            vec camdir_normalized = camdir;
            camdir_normalized.normalize();
            selected_node->pos = game::player1->o + camdir_normalized.mul(selected_dist);
            selected_node->pos_changed = true;
        }
    }


    void CVisualScriptSystem::connect_nodes(CScriptNode *from, CScriptNode *to)
    {
        to->parents.push_back(from);
        from->children.push_back(to);

        // add a connection curve
        geom::CBezierCurve newcurve;
        from->relations.push_back(newcurve);
        from->pos_changed = true;
    }


    void CVisualScriptSystem::update_input(int key, bool isdown)
    {
        switch( - key)
        {
            case SDL_BUTTON_LEFT:
                
                if(!dragging_new_relation && isdown && !selection_blocked_by_geometry) // start dragging
                {
                    for(unsigned int i=0; i<nodes.size(); i++)
                    {
                        float dist = 0.0f;
                        int orient = VSCRIPT_BOX_NO_INTERSECTION;
                        vec p = nodes[i]->pos;

                        if(rayboxintersect(p, vec(boxsize), camera1->o, camdir, dist, orient))
                        {
                            dragging_new_relation = true;
                        }
                    }
                }
                if(dragging_new_relation && !isdown) // stop dragging
                {
                    dragging_new_relation = false;
                }

                break;


            case SDL_BUTTON_RIGHT:

                if(isdown && nullptr != hovered_node)
                {
                    /// key pressed
                    selected_node = hovered_node;
                    move_pos_start = camera1->o;
                    node_pos_start = selected_node->pos;
                    moving_entity = true;
                }
                else 
                {
                    /// key released
                    if(nullptr != selected_node)
                    {
                        moving_entity = false;
                        selected_node->pos_changed = false;
                        selected_node = nullptr;
                    }
                }
                break;
        }
    }


    void CVisualScriptSystem::sync_all_timers()
    {
        for(unsigned int i=0; i<nodes.size(); i++)
        {
            if(NODE_TYPE_TIMER == nodes[i]->type) nodes[i]->reset();
        }
    }


    void CVisualScriptSystem::delete_all_nodes()
    {
        nodes.clear();
    }


    void CVisualScriptSystem::update_timers()
    {
        for(unsigned int i=0; i<nodes.size(); i++)
        {
            nodes[i]->this_time = SDL_GetTicks();
            if(NODE_TYPE_TIMER == nodes[i]->type) nodes[i]->in();
        }
    }


    void CVisualScriptSystem::start_rendering()
    {
        notextureshader->set();
        gle::enablevertex();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        enablepolygonoffset(GL_POLYGON_OFFSET_LINE);
    }


    void CVisualScriptSystem::end_rendering()
    {
        disablepolygonoffset(GL_POLYGON_OFFSET_LINE);
        gle::clearvbo();
        gle::clearebo();
        gle::disablevertex();
    }


    void CVisualScriptSystem::render_nodes()
    {
        hovered_node = nullptr;
        
        for(unsigned int i=0; i<nodes.size(); i++) 
        {
            float dist = 0.0f;
            int orient = VSCRIPT_BOX_NO_INTERSECTION;

            rayboxintersect(nodes[i]->pos, vec(boxsize), camera1->o, camdir, dist, orient);
            nodes[i]->selected = (orient != VSCRIPT_BOX_NO_INTERSECTION);

            // render a 200ms long color effect once its activated
            if( (nodes[i]->this_time - nodes[i]->last_time)  < INEXOR_VSCRIPT_ACTIVE_NODE_TIMER_INTERVAL) nodes[i]->box_color = VSCRIPT_COLOR_TRIGGERED;
            else nodes[i]->box_color = nodes[i]->default_box_color;
            nodes[i]->render(orient, selection_blocked_by_geometry);
        }

        // which node is selected?
        for(unsigned int i=0; i<nodes.size(); i++)
        {
            if(nodes[i]->selected && nullptr != nodes[i]) hovered_node = nodes[i];
        }
    }


    void CVisualScriptSystem::render_debug_rays()
    {
        glBegin(GL_LINES);
        gle::color(vec::hexcolor(VSCRIPT_COLOR_DEBUG_RAY));
        glLineWidth(10.0f);
        for(unsigned int h=0; h<rays.size(); h++)
        {
            glVertex3f(rays[h].pos.x,rays[h].pos.y,rays[h].pos.z);
            glVertex3f(rays[h].target.x,rays[h].target.y,rays[h].target.z);
        }
        glLineWidth(1.0f);
        glEnd();
    }


    void CVisualScriptSystem::render_node_relations()
    {
        if(!nodes.size()) return;

        for(unsigned int i=0; i<nodes.size(); i++)
        {   
            for(unsigned int e = 0; e < nodes[i]->children.size(); e++)
            {
                geom::CBezierCurve *tmp = &nodes[i]->relations[e];

                if(nodes[i]->pos_changed || nodes[i]->children[e]->pos_changed)
                {
                    tmp->ClearAllPoints();
            
                    // generate a nice and smooth curve between two nodes
                    vec t = nodes[i]->pos;
                    vec n = nodes[i]->children[e]->pos;
                    vec interpol1 = vec(t.x, t.y, t.z - 40.0f);
                    vec interpol2 = vec(n.x, n.y, n.z + 40.0f);

                    t.x += boxsize/2;
                    t.y += boxsize/2;
                    n.x += boxsize/2;
                    n.y += boxsize/2;
                    n.z += boxsize;

                    tmp->AddParameterPoint(t);
                    tmp->AddParameterPoint(interpol1);
                    tmp->AddParameterPoint(interpol2);
                    tmp->AddParameterPoint(n);
                    
                    /// recompute cache
                    tmp->ComputeCache();
                }

                glBegin(GL_LINES);
                gle::color(vec::hexcolor(VSCRIPT_COLOR_TRIGGERED));
                glLineWidth(10.0f);

                for(unsigned int h=0; h<tmp->GetCachedPointsSize() -1; h++)
                {
                    geom::SCustomOutputPoint t = tmp->GetPoint_ByIndex(h);
                    geom::SCustomOutputPoint n = tmp->GetPoint_ByIndex(h   +1);
                    glVertex3f(t.pos.x, t.pos.y, t.pos.z);
                    glVertex3f(n.pos.x, n.pos.y, n.pos.z);
                }
                
                glLineWidth(1.0f);
                glEnd();
            }
        }
    }




    void deleteallnodes()
    {
        vScript3D.delete_all_nodes();
    }
    COMMAND(deleteallnodes, "");


    CScriptNode* a;
    CScriptNode* b;
    CScriptNode* c;
    CScriptNode* d;

    
    void test_a()
    {
        a = vScript3D.add_node(NODE_TYPE_TIMER, 7, "1000", "0", "1000", "0", "TimerNode1", "Hello world", "0");
    }
    COMMAND(test_a, "");


    void test_b()
    {
        b = vScript3D.add_node(NODE_TYPE_SLEEP, 1, "150");
        vScript3D.connect_nodes(a,b);
    }
    COMMAND(test_b, "");


    void test_c()
    {
        c = vScript3D.add_node(NODE_TYPE_FUNCTION, 2, "0" , "Hallo Welt");
        vScript3D.connect_nodes(b,c);
    }
    COMMAND(test_c, "");

    void test_d()
    {
        d = vScript3D.add_node(NODE_TYPE_AREA_BLOCK, 2, "Kommentar", "Hallo Welt Bereich");
    }
    COMMAND(test_d, "");

};
};
