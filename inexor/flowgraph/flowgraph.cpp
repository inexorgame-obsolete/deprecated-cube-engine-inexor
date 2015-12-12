#include "inexor/flowgraph/flowgraph.h"
#include "inexor/geom/curves/bezier/bezier.h"
using namespace inexor::geom;

extern selinfo sel, lastsel, savedsel;
extern bool editmode;
extern int gridsize;


namespace inexor {
namespace vscript {

    CVisualScriptSystem vScript3D;
    CVisualScriptWorker vWorker;

    CVisualScriptSystem::CVisualScriptSystem() 
    {
    }


    CVisualScriptSystem::~CVisualScriptSystem() 
    {
        /// @bug does that even work?
        for(unsigned int i=0; i<nodes.size(); i++) {
            delete (nodes[i]);
        }
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
        va_start(parameters, parameter_count);

        /// Please note: the old command engine of Inexor will always pass every parameter as char* 
        /// so using std::string is fine.
        /// In this vector we will store the arguments as strings
        std::vector<std::string> arguments;

        /// Store the current argument in the std::string vector
        for(unsigned int i=0; i<parameter_count; i++)
        {
            arguments.push_back(va_arg(parameters, char *));
        }
        va_end(parameters);
    
        /// add new node depending on the type
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
                vWorker.add_job(created_node);
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
        selected_node = nullptr;

        /// TODO: do we need this here again?
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

            /// TODO: update time!
            if(NODE_TYPE_TIMER != nodes[i]->type) nodes[i]->this_time = unique_execution_pass_timestamp;

            gle::color(vec::hexcolor(nodes[i]->box_color));
            renderbox(p, orient, nodes[i]->box_color);

            /// no matter where the box is being selected, render help lines
            if(orient != VSCRIPT_BOX_NO_INTERSECTION) 
            {
                gle::color(vec::hexcolor(VSCRIPT_COLOR_GRAY));
                renderboxhelplines(p);
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
            if(nodes[i]->selected) selected_node = nodes[i];
    }


    void CVisualScriptSystem::render_node_relations()
    {
        if(!nodes.size()) return;

        for(unsigned int i=0; i<nodes.size(); i++)
        {   
            /// Render all outgoing relations
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

                /// add points
                curve.AddParameterPoint(t);
                curve.AddParameterPoint(interpol1);
                curve.AddParameterPoint(interpol2);
                curve.AddParameterPoint(n);

                /// compute!
                curve.ComputeCache();

                /// render curve as list of small lines
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
                /// reset line width
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

        /// Update execution time
        unique_execution_pass_timestamp = SDL_GetTicks();
        //conoutf(CON_DEBUG, "unique_execution_pass_timestamp: %d", unique_execution_pass_timestamp);

        /// If this is a node, run it!
        for(int i=0; i<nodes.size(); i++) 
        {
            if(NODE_TYPE_TIMER == nodes[i]->type)
            {
                nodes[i]->this_time = unique_execution_pass_timestamp;
                vWorker.run_jobs();
            }
        }
    }


    void CVisualScriptSystem::connect_nodes(CScriptNode *from, CScriptNode *to)
    {
        to->parents.push_back(from);
        from->children.push_back(to);
    }


    //#define INEXOR_VSCRIPT_MOUSE_DEBUGGING 1

    void CVisualScriptSystem::process_change(int key, bool isdown)
    {
        switch( - key) /// TODO: why the minus?
        {
            case SDL_BUTTON_LEFT:
                
                #ifdef INEXOR_VSCRIPT_MOUSE_DEBUGGING
                    if(isdown) conoutf(CON_DEBUG, "left click: making a new relation.");
                    else conoutf(CON_DEBUG, "left click: operation finished.");
                #endif

                /// stopping to drag
                if(dragging_new_relation && !isdown)
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

                /// starting to drag
                if(!dragging_new_relation && isdown)
                {
                    for(unsigned int i=0; i<nodes.size(); i++)
                    {
                        /// check ray-box intersection
                        float dist = 0.0f;
                        int orient = VSCRIPT_BOX_NO_INTERSECTION;
                        vec p = nodes[i]->position;

                        if(rayboxintersect(p, vec(boxsize), camera1->o, camdir, dist, orient))
                        {
                            /// save dragging information
                            drag_pos_start = p;
                            camera_offset_start = camera1->o;
                            camera_last_pos = camera1->o;

                            /// this is where we start
                            drag_pos_current = p;
                            dragging_new_relation = true;
                        }
                    }
                }                
                break;


            case SDL_BUTTON_RIGHT:

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




    /// Workers and jobs
    CVisualScriptWorker::CVisualScriptWorker()
    {
    }

    CVisualScriptWorker::~CVisualScriptWorker()
    {
    }

    void CVisualScriptWorker::add_job(CScriptNode* node)
    {
        CJob j;
        j.node = node;
        j.started = false;
        j.done = false;
        jobs.push_back(j);
    }



    void CVisualScriptWorker::run_jobs()
    {
        unsigned long start_time = SDL_GetTicks();

        for(unsigned int i=0; i<jobs.size(); i++)
        {
            if(!jobs.at(i).done)
            {
                jobs.at(i).started = true;
                jobs.at(i).node->done_pointer = & jobs.at(i).done;
                jobs.at(i).node->script_execution_start = start_time;
                jobs.at(i).node->in();
            }
        }
    }



    void deleteallnodes()
    {
        vScript3D.clear_all_nodes();
    }
    COMMAND(deleteallnodes, "");


    void addconoutf(char* message)
    {
        vScript3D.add_node(NODE_TYPE_FUNCTION, 2, "0" /*FUNCTION_CONOUTF*/, message);
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
    
    CScriptNode* a;
    CScriptNode* b;
    CScriptNode* c;

    /// Testing and debugging
    void test_a()
    {
        a = vScript3D.add_node(NODE_TYPE_TIMER, 7, "5000", "0", "1000", "0", "TimerNode1", "Hello world", "0");
    }
    COMMAND(test_a, "");

    void test_b()
    {
        //b = vScript3D.add_node(NODE_TYPE_FUNCTION, 2, "0" /*FUNCTION_CONOUTF*/, "Hello World");
        b = vScript3D.add_node(NODE_TYPE_SLEEP, 1, "1337");
        vScript3D.connect_nodes(a,b);
    }
    COMMAND(test_b, "");

    void test_c()
    {
        //b = vScript3D.add_node(NODE_TYPE_FUNCTION, 2, "0" /*FUNCTION_CONOUTF*/, "Hello World");
        c = vScript3D.add_node(NODE_TYPE_FUNCTION, 2, "1" /*FUNCTION_PLAYSOUND*/, "52" /*S_V_BASECAP*/);
        vScript3D.connect_nodes(b,c);
    }
    COMMAND(test_c, "");

/// end of namespace
};
};
