#include "inexor/flowgraph/flowgraph.h"
#include "inexor/geom/curves/bezier/bezier.h"
#include "inexor/fpsgame/game.h"
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
        }

        if(nullptr != created_node)  nodes.push_back(created_node);
        return created_node;
    }


    void CVisualScriptSystem::update_drag_n_drop()
    {
        if(nullptr != selected_node)
        {
            static float selected_dist = 0.0f;
            static bool notCalculated = true;
            if(notCalculated)
            {
                selected_dist = selected_node->position.dist(game::player1->o);
                notCalculated = false;
            }
            
            vec camdir_normalized = camdir;
            camdir_normalized.normalize();
            selected_node->position = game::player1->o + camdir_normalized.mul(selected_dist);
            selected_node->pos_changed = true;
        }
    }


    void CVisualScriptSystem::connect_nodes(CScriptNode *from, CScriptNode *to)
    {
        to->parents.push_back(from);
        from->children.push_back(to);
    }


    void CVisualScriptSystem::disconnect_nodes(CScriptNode* from, CScriptNode* to)
    {
        /// TODO:...
    }


    void CVisualScriptSystem::process_change(int key, bool isdown)
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
                    move_pos_start = camera1->o;
                    node_pos_start = selected_node->position;
                    moving_entity = true;
                }
                else 
                {
                    /// key released
                    moving_entity = false;
                    selected_node = nullptr;
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


    void deleteallnodes()
    {
        vScript3D.delete_all_nodes();
    }
    COMMAND(deleteallnodes, "");


    /*
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
