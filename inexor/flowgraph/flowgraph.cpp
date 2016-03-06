#include "inexor/flowgraph/flowgraph.hpp"
#include "inexor/fpsgame/game.hpp"
#include "inexor/flowgraph/sleep/fl_sleep.hpp"
#include "inexor/flowgraph/timer/fl_timer.hpp"
#include "inexor/flowgraph/comments/fl_comment.hpp"
#include "inexor/flowgraph/functions/fl_functionbase.hpp"
#include "inexor/flowgraph/functions/fl_functions.hpp"

#include "inexor/flowgraph/areas/block/fl_area_block.hpp"
#include "inexor/flowgraph/areas/sphere/fl_area_sphere.hpp"

#include "inexor/geom/geom.hpp"
#include "inexor/geom/curves/bezier/bezier.hpp"

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


    void CVisualScriptSystem::update_relation_linker()
    {
        if(nullptr != relation_start_node)
        {
            static float selected_dist = 0.0f;
            static bool calculated = false;
            if(!calculated)
            {
                selected_dist = relation_drag_start.dist(game::player1->o);
                calculated=true;
            }

            vec camdir_normalized = camdir;
            camdir_normalized.normalize();
            vec drag_target_pos = game::player1->o+camdir_normalized.mul(selected_dist);
            
            conoutf(CON_DEBUG, "from %f %f %f to %f %f %f ",drag_target_pos.x,drag_target_pos.y,drag_target_pos.z,
                    relation_drag_start.x,relation_drag_start.y,relation_drag_start.z);

            
            start_rendering();
            glBegin(GL_LINES);

            gle::color(vec::hexcolor(VSCRIPT_COLOR_DEBUG_RAY));

            glVertex3f(drag_target_pos.x,drag_target_pos.y,drag_target_pos.z);
            glVertex3f(relation_drag_start.x,relation_drag_start.y,relation_drag_start.z);
            glEnd();
            end_rendering();


            /*
            /// calc bezier curve
            tmp_relation_linker_curve.AddParameterPoint(relation_start_node->pos);
            tmp_relation_linker_curve.AddParameterPoint(drag_target_pos);
            tmp_relation_linker_curve.ComputeCache();

            /// render curve
            glBegin(GL_LINES);
            for(unsigned int i=0; i<tmp_relation_linker_curve.GetCachedPointsSize(); i++)
            {
                geom::SCustomOutputPoint p = tmp_relation_linker_curve.GetPoint_ByIndex(i);
                glVertex3f(p.pos.x,p.pos.y,p.pos.z);
            }
            glEnd();
            */

            // TODO: check if we can make a new relation!
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
        switch( - key) // why the minus?
        {
            // left mouse button for dragging relations
            case SDL_BUTTON_LEFT:
            {
                if(!dragging_new_relation && isdown && !selection_blocked_by_geometry)
                {
                    for(unsigned int i=0; i<nodes.size(); i++)
                    {
                        float dist = 0.0f;
                        int orient = VSCRIPT_BOX_NO_INTERSECTION;
                        vec p = nodes[i]->pos;

                        if(rayboxintersect(p, vec(boxsize), camera1->o, camdir, dist, orient))
                        {                        
                            relation_drag_start = p;
                            relation_start_node = nodes[i];
                            dragging_new_relation=true;
                        }
                    }
                }
                if(dragging_new_relation && !isdown) // stop dragging
                {
                    if(nullptr !=hovered_node)
                    {
                        // do not link nodes to itself!
                        if(hovered_node != relation_start_node)
                        {
                            // link nodes together!
                            conoutf(CON_DEBUG, "Added new relation!");
                            connect_nodes(relation_start_node,hovered_node);
                        }
                    }

                    relation_start_node = nullptr;
                    dragging_new_relation = false;
                }
                break;
            }

            /// right mouse button for moving
            case SDL_BUTTON_RIGHT:
            {
                if(isdown && nullptr != hovered_node)
                {
                    /// key pressed
                    selected_node = hovered_node;
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

    
    void test_a()
    {
        a = vScript3D.add_node(NODE_TYPE_TIMER, 7, "1000", "0", "1000", "0", "TimerNode1", "Hello world", "0");
    }
    COMMAND(test_a, "");



    void test_b()
    {
        b = vScript3D.add_node(NODE_TYPE_FUNCTION,2,"0","Hallo Welt");
    }
    COMMAND(test_b,"");



    void test_c()
    {
        c = vScript3D.add_node(NODE_TYPE_FUNCTION, 2, "1", "14");
    }
    COMMAND(test_c, "");


};
};
