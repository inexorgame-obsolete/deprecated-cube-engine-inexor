#include "inexor/flowgraph/flowgraph.h"
#include "inexor/geom/curves/bezier/bezier.h"
using namespace inexor::geom;

extern selinfo sel, lastsel, savedsel;
extern bool editmode;
extern int gridsize;


namespace inexor {
namespace vscript {

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

        
        #ifdef INEXOR_VSCRIPT_DEBUG_RAYS
            debug_ray dr_tmp;
            dr_tmp.pos = camera1->o;
            dr_tmp.target = target;
            rays.push_back(dr_tmp);
        #endif    


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

                #ifdef INEXOR_VSCRIPT_ADDNODE_DEBUG
                    conoutf(CON_DEBUG, "I added the following timer node: interval: %d, startdelay: %d, limit: %d, cooldown: %d, name: %s, comment: %s, type: %d", interval, startdelay, limit, cooldown, name, comment, timer_format);
                #endif

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
        }

        if(nullptr != created_node)  nodes.push_back(created_node);
        return created_node;
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
                    SCustomOutputPoint t = curve.GetPoint_ByIndex(h);
                    SCustomOutputPoint n = curve.GetPoint_ByIndex(h  +1);
                    glVertex3f(t.pos.x, t.pos.y, t.pos.z);
                    glVertex3f(n.pos.x, n.pos.y, n.pos.z);
                }
                glLineWidth(1.0f);
                glEnd();
            }
        }
    }
    

    void CVisualScriptSystem::update_timers_and_events()
    {
        /// Please note: every timer node will be told that no time 
        /// has passed by executing other nodes. They all will be executed simultaneously.
        /// This keeps them synchronized.

        unique_execution_pass_timestamp = SDL_GetTicks();
        //conoutf(CON_DEBUG, "unique_execution_pass_timestamp: %d", unique_execution_pass_timestamp);

        /// If this is a node, run it!
        for(int i=0; i<nodes.size(); i++) 
        {
            if(NODE_TYPE_TIMER == nodes[i]->type)
            {
                nodes[i]->this_time = unique_execution_pass_timestamp;
                nodes[i]->in();
            }
        }
    }


    void CVisualScriptSystem::update_entity_positions()
    {
        if(nullptr != selected_node)
        {
            /// apply change of position
            vec newpos = selected_node->position;
            newpos.sub(player->deltapos*2);
            selected_node->position = newpos;
        }
    }


    void CVisualScriptSystem::connect_nodes(CScriptNode *from, CScriptNode *to)
    {
        to->parents.push_back(from);
        from->children.push_back(to);
    }

    
    #define INEXOR_VSCRIPT_MOUSE_DEBUGGING 1


    void CVisualScriptSystem::process_change(int key, bool isdown)
    {
        switch( - key)
        {
            case SDL_BUTTON_LEFT:
                
                #ifdef INEXOR_VSCRIPT_MOUSE_DEBUGGING
                    if(isdown) conoutf(CON_DEBUG, "left click: making a new relation.");
                    else conoutf(CON_DEBUG, "left click: operation finished.");
                #endif


                if(!dragging_new_relation && isdown && !selection_blocked_by_geometry) // start dragging
                {
                    for(unsigned int i=0; i<nodes.size(); i++)
                    {
                        /// check ray-box intersection
                        float dist = 0.0f;
                        int orient = VSCRIPT_BOX_NO_INTERSECTION;
                        vec p = nodes[i]->position;

                        if(rayboxintersect(p, vec(boxsize), camera1->o, camdir, dist, orient))
                        {
                            dragging_new_relation = true;
 
                            drag_pos_start = p;
                            drag_pos_current = p;
                        }
                    }
                }                

                if(dragging_new_relation && !isdown) // stop dragging
                {
                    /*
                    /// TODO: end dragging!
                    if(camera_ray_node_box_intersection(all_nodes, dragging_target_pos_offset))
                    {
                        /// TODO: add relation to target
                        add_relation();
                        /// save dragging_target_pos_offset
                    }
                    */
                    dragging_new_relation = false;
                }

                break;


            case SDL_BUTTON_RIGHT:

                if(isdown && nullptr != hovered_node)
                {
                    /// key pressed
                    selected_node = hovered_node;
                    moving_entity = true;
                }
                else 
                {
                    /// key released
                    moving_entity = false;
                    selected_node = nullptr;
                }

                #ifdef INEXOR_VSCRIPT_MOUSE_DEBUGGING
                    if(isdown) conoutf(CON_DEBUG, "right click: dragging entity around.");
                    else conoutf(CON_DEBUG, "right click: dragging finished.");
                #endif

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
    

    void CVisualScriptSystem::clear_all_nodes()
    {
        nodes.clear();
    }

    /// TODO: implemen node relation manager
    /*

    void deleteallnodes()
    {
        vScript3D.clear_all_nodes();
    }
    COMMAND(deleteallnodes, "");


    void addconoutf(char* message)
    {
        vScript3D.add_node(NODE_TYPE_FUNCTION, 2, "0", message);
    }
    COMMAND(addconoutf, "s");


    void addtimer(char* interval, char* startdelay, char* limit, char* cooldown, char* name, char* comment, char* timer_format)
    {
        vScript3D.add_node(NODE_TYPE_TIMER, 7, interval, startdelay, limit, cooldown, name, comment, timer_format);
    }
    COMMAND(addtimer, "sssssss");


    void synctimers()
    {
        vScript3D.sync_all_timers();
    }
    COMMAND(synctimers, "");


    void addcomment(char* node_comment, char* node_name)
    {
        vScript3D.add_node(NODE_TYPE_COMMENT, 2, node_comment, node_name);
    }
    COMMAND(addcomment, "ss");
    
    */

    CScriptNode* a;
    CScriptNode* b;
    CScriptNode* c;
    CScriptNode* d;

    
    void test_a()
    {
        a = vScript3D.add_node(NODE_TYPE_TIMER, 7, "5000", "0", "1000", "0", "TimerNode1", "Hello world", "0");
    }
    COMMAND(test_a, "");

    void test_b()
    {
        b = vScript3D.add_node(NODE_TYPE_SLEEP, 1, "1500");
        vScript3D.connect_nodes(a,b);
    }
    COMMAND(test_b, "");


    void test_c()
    {
        c = vScript3D.add_node(NODE_TYPE_FUNCTION, 2, "0" , "Hallo Welt");
        vScript3D.connect_nodes(b,c);
    }
    COMMAND(test_c, "");

};
};
