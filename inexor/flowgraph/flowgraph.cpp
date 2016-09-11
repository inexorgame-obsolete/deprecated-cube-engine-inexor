#include "inexor/flowgraph/flowgraph.hpp"
#include "inexor/fpsgame/game.hpp"
#include "inexor/flowgraph/sleep/fl_sleep.hpp"
#include "inexor/flowgraph/timer/fl_timer.hpp"
#include "inexor/flowgraph/comments/fl_comment.hpp"

// experimental
#include "inexor/flowgraph/memory/fl_membase.hpp"
#include "inexor/flowgraph/memory/bool/fl_mem_bool.hpp"

// functions
#include "inexor/flowgraph/functions/base/fl_functionbase.hpp"
#include "inexor/flowgraph/functions/fl_functions.hpp"

// areas
#include "inexor/flowgraph/areas/block/fl_area_block.hpp"
#include "inexor/flowgraph/areas/sphere/fl_area_sphere.hpp"
#include "inexor/flowgraph/areas/cone/fl_area_cone.hpp"
#include "inexor/flowgraph/areas/cylinder/fl_area_cylinder.hpp"

// operators
#include "inexor/flowgraph/operators/fl_operator.hpp"

// geometry
#include "inexor/geom/geom.hpp"
#include "inexor/geom/curves/bezier/bezier.hpp"

// events
#include "inexor/flowgraph/events/base/fl_event_base.hpp"
#include "inexor/flowgraph/events/areas/base/fl_area_event_base.hpp"
#include "inexor/flowgraph/events/areas/player_interaction/fl_event_player_area_interaction.hpp"

// if conditions
#include "inexor/flowgraph/if/fl_if_condition.hpp"


// use the engine's selection model
extern selinfo sel, lastsel, savedsel;
extern bool editmode;
extern int gridsize;

enum VSCRIPT_ENTITY_BOX_ORIENTATION
{
    INEXOR_VSCRIPT_BOX_NO_INTERSECTION = -1,
    INEXOR_VSCRIPT_BOX_LEFT,
    INEXOR_VSCRIPT_BOX_RIGHT,
    INEXOR_VSCRIPT_BOX_FRONT,
    INEXOR_VSCRIPT_BOX_BACK,
    INEXOR_VSCRIPT_BOX_BOTTOM,
    INEXOR_VSCRIPT_BOX_TOP
};

namespace inexor {
namespace vscript {

    // TODO: make CVisualScriptSystem a singleton class!
    CVisualScriptSystem vScript3D;

    CVisualScriptSystem::CVisualScriptSystem() 
    {
        selection_blocked_by_geometry = false;
    }

    CVisualScriptSystem::~CVisualScriptSystem() 
    {
        // TODO: we have to clear the dynamicly allocated memory!
        for(unsigned int i=0; i<nodes.size(); i++) delete(nodes[i]);
        nodes.clear();
    }

    // creates a node and allocates memory for it
    CScriptNode* CVisualScriptSystem::add_node(INEXOR_VSCRIPT_NODE_TYPE type, int parameter_count, ...)
    {
        // this memory must be deleted afterwards!
        CScriptNode* created_node = nullptr;

        vec target = vec(sel.o.x,sel.o.y,sel.o.z);
        vec offset = vec(gridsize/2,gridsize/2,gridsize/2);
        target.add(offset);

        // convert parameters to parameter list
        va_list parameters;
        std::vector<std::string> arguments;
        va_start(parameters, parameter_count);
        for(unsigned int i=0; i<parameter_count; i++)
        {
            arguments.push_back(va_arg(parameters, char*));
        }
        va_end(parameters);

        switch(type)
        {
            case INEXOR_VSCRIPT_NODE_TYPE_TIMER:
            {
                unsigned int interval   = atoi(arguments[0].c_str());
                unsigned int startdelay = atoi(arguments[1].c_str());
                unsigned int limit      = atoi(arguments[2].c_str());
                unsigned int cooldown   = atoi(arguments[3].c_str());
                const char* name        = arguments[4].c_str();
                const char* comment     = arguments[5].c_str();
                if(0 == interval) interval = 1000;

                /// TODO: implement other time formats
                INEXOR_VSCRIPT_TIME_FORMAT timer_format = INEXOR_VSCRIPT_TIME_FORMAT_MILISECONDS;
                created_node = new CTimerNode(target, interval, startdelay, limit, cooldown, timer_format);
                created_node->set_name(name);
                created_node->set_comment(comment);
                sync_all_timers();
                break;
            }

            case INEXOR_VSCRIPT_NODE_TYPE_COMMENT:
            {
                if(!strlen(arguments[0].c_str()))
                {
                    conoutf(CON_DEBUG, "[3DVS-comments] error: empty string as comment!");
                    break;
                }
                created_node = new CCommentNode(target);
                created_node->set_comment(arguments[0].c_str());
                break;
            }

            case INEXOR_VSCRIPT_NODE_TYPE_FUNCTION:
            {
                if (!strlen(arguments[0].c_str()))
                {
                    conoutf(CON_DEBUG, "[3DVS-functions] error: no function name speficied!");
                    break;
                }

                switch(atoi(arguments[0].c_str()))
                {
                    case INEXOR_VSCRIPT_FUNCTION_CONOUTF:
                    {
                        if (!strlen(arguments[1].c_str()))
                        {
                            conoutf(CON_DEBUG, "[3DVS-functions-conoutf] error: no output text specified!");
                            break;
                        }
                        created_node = new CFunctionConoutfNode(target, arguments[1].c_str());
                        break;
                    }
                    case INEXOR_VSCRIPT_FUNCTION_PLAYSOUND:
                    {
                        if (!strlen(arguments[1].c_str()))
                        {
                            conoutf(CON_DEBUG, "[3DVS-functions-playsound] error: sound to play specified!");
                            break;
                        }
                        // add a sound player function
                        created_node = new CFunctionPlaysoundNode(target, arguments[1].c_str());
                        break;
                    }
                }
                break;
            }

            case INEXOR_VSCRIPT_NODE_TYPE_SLEEP:
            {
                unsigned int wait_time   = atoi(arguments[0].c_str());
                if(0 == wait_time) wait_time = 500;
                created_node = new CSleepNode(target, wait_time); 
                break;
            }

            case INEXOR_VSCRIPT_NODE_TYPE_AREA_BOX:
            {
                float area_width  = atof(arguments[0].c_str());
                float area_height = atof(arguments[1].c_str());
                float area_depth  = atof(arguments[2].c_str());
                created_node = new CCubeAreaNode(target, area_width, area_height, area_depth);
                created_node->set_name("box");
                created_node->set_comment("box area");
                break;
            }

            case INEXOR_VSCRIPT_NODE_TYPE_AREA_SPHERE:
            {
                float radius = atof(arguments[0].c_str());
                created_node = new CSphereAreaNode(target, radius);
                created_node->set_name("sphere");
                created_node->set_comment("spheric area");
                break;
            }

            case INEXOR_VSCRIPT_NODE_TYPE_AREA_CONE:
            {
                float height = atof(arguments[0].c_str());
                float radius = atof(arguments[1].c_str());
                created_node = new CConeAreaNode(target, height, radius);
                created_node->set_name("cone");
                created_node->set_comment("cone area");
                break;
            }

            case INEXOR_VSCRIPT_NODE_TYPE_AREA_CYLINDER:
            {
                float height = atof(arguments[0].c_str());
                float radius = atof(arguments[1].c_str());
                created_node = new CCylinderAreaNode(target, height, radius);
                created_node->set_name("cylinder");
                created_node->set_comment("cylinder area");
                break;
            }

            case INEXOR_VSCRIPT_NODE_TYPE_MEMORY_INTEGER:
            {
                bool constant_value = false;
                if(1 == atoi(arguments[1].c_str())) constant_value = true;
                created_node = new CMemIntegerNode(target, true, true, atoi(arguments[0].c_str()), constant_value);
                created_node->set_name("integer");
                created_node->set_comment("memory block for whole numbers");
                break;
            }

            case INEXOR_VSCRIPT_NODE_TYPE_MEMORY_FLOAT:
            {
                bool constant_value = false;
                if(1 == atoi(arguments[1].c_str())) constant_value = true;
                created_node = new CMemFloatNode(target, true, true, atof(arguments[0].c_str()), constant_value);
                created_node->set_name("float");
                created_node->set_comment("memory block for float numbers");
                break;
            }

            case INEXOR_VSCRIPT_NODE_TYPE_MEMORY_BOOL:
            {
                bool constant_value = false;
                if(1 == atoi(arguments[1].c_str())) constant_value = true;
                created_node = new CMemBoolNode(target, atof(arguments[0].c_str()), constant_value);
                created_node->set_name("bool");
                created_node->set_comment("memory block for boolean expressions");
                break;
            }

            case INEXOR_VSCRIPT_NODE_TYPE_IF:
            {
                created_node = new CIfNode(target);
                created_node->set_name("if-query");
                created_node->set_comment("what if..?");
                break;
            }

            case INEXOR_VSCRIPT_NODE_TYPE_EVENT:
            {
                switch(atoi(arguments[0].c_str()))
                {
                    case INEXOR_VSCRIPT_EVENT_TYPE_PLAYER_ENTER_AREA:
                    {
                        created_node = new CPlayerAreaInteractionEventNode(target, INEXOR_VSCRIPT_EVENT_TYPE_PLAYER_ENTER_AREA);
                        created_node->set_name("player-enter-area-event");
                        created_node->set_comment("Just enter that damn area!");
                        break;
                    }
                    case INEXOR_VSCRIPT_EVENT_TYPE_PLAYER_LEAVE_AREA:
                    {
                        created_node = new CPlayerAreaInteractionEventNode(target, INEXOR_VSCRIPT_EVENT_TYPE_PLAYER_LEAVE_AREA);
                        created_node->set_name("player-leave-area-event");
                        created_node->set_comment("Just leave that damn area!");
                        break;
                    }
                    case INEXOR_VSCRIPT_EVENT_TYPE_PLAYER_SUICIDE:
                    {
                        created_node = new CPlayerAreaInteractionEventNode(target, INEXOR_VSCRIPT_EVENT_TYPE_PLAYER_SUICIDE);
                        created_node->set_name("player-suicide-event");
                        created_node->set_comment("Don't kill yourself, idiot!");
                        break;
                    }
                    default:
                    {
                        conoutf(CON_DEBUG, "[3DVS-area-player-interaction-event] unknown event type!");
                        break;
                    }
                }
                break;
            }

            case INEXOR_VSCRIPT_NODE_TYPE_OPERATOR:
            {
                switch(atoi(arguments[0].c_str()))
                {
                    case INEXOR_VSCRIPT_OPERATOR_TYPE_INCREMENT:
                    {
                        created_node = new COperatorNode(target, INEXOR_VSCRIPT_OPERATOR_TYPE_INCREMENT);
                        created_node->set_name("operator ++");
                        created_node->set_comment("increments integers and float values");
                        break;
                    }
                    case INEXOR_VSCRIPT_OPERATOR_TYPE_DECREMENT:
                    {
                        created_node = new COperatorNode(target, INEXOR_VSCRIPT_OPERATOR_TYPE_DECREMENT);
                        created_node->set_name("operator --");
                        created_node->set_comment("decrements integers and float values");
                        break;
                    }
                    case INEXOR_VSCRIPT_OPERATOR_TYPE_SETNULL:
                    {
                        created_node = new COperatorNode(target, INEXOR_VSCRIPT_OPERATOR_TYPE_SETNULL);
                        created_node->set_name("operator = 0");
                        created_node->set_comment("sets integers and float values to zero");
                        break;
                    }
                    case INEXOR_VSCRIPT_OPERATOR_TYPE_SETVAL:
                    {
                        created_node = new COperatorNode(target, INEXOR_VSCRIPT_OPERATOR_TYPE_SETVAL);
                        created_node->set_name("operator = [value]");
                        created_node->set_comment("sets integers and float values to [value]");
                        break;
                    }
                    default:
                    {
                        conoutf(CON_DEBUG, "[3DVS-operator] error: unknown operator type!");
                        break;
                    }
                }
            }
        }

        if(nullptr != created_node)
        {
            nodes.push_back(created_node);
        }
        return created_node;
        // TODO: delete created_node at program exit!
    }
    
    void CVisualScriptSystem::remove_node(CScriptNode* node)
    {
        // TODO: implement "remove node"!
    }

    // calculates the distance from editor to entity
    void CVisualScriptSystem::update_drag_n_drop()
    {
        if(nullptr != selected_node)
        {
            static float selection_dist = 0.0f;
            if(!distance_calculated)
            {
                selection_dist = selected_node->pos.dist(game::player1->o);
                distance_calculated = true;
            }
            
            vec camdir_normalized = camdir;
            camdir_normalized.normalize();
            selected_node->pos = game::player1->o + camdir_normalized.mul(selection_dist);
            selected_node->pos_changed = true;
        }
    }

    // updates positions of relation curves and renders them
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

            // render line            
            start_rendering();
            glBegin(GL_LINES);
            glLineWidth(5.0f);
            gle::color(vec::hexcolor(INEXOR_VSCRIPT_COLOR_TIMER));
            
            float box_center_offset = boxsize/2;
            glVertex3f(drag_target_pos.x,drag_target_pos.y,drag_target_pos.z);
            glVertex3f(relation_drag_start.x+box_center_offset ,relation_drag_start.y+box_center_offset ,relation_drag_start.z+box_center_offset );

            glLineWidth(1.0f);
            glEnd();
            end_rendering();
        }
    }

    // adds a new relation between the nodes and a new curve for the relation
    void CVisualScriptSystem::connect_nodes(CScriptNode *from, CScriptNode *to)
    {
        // store parent and chil in each other's vectors
        to->parents.push_back(from);
        from->children.push_back(to);

        // create a new relation curve
        SNodeRelation newcurve;
        newcurve.from = from;
        newcurve.to = to;

        // store relation!
        relations.push_back(newcurve);
        from->relations.push_back(newcurve);
        from->pos_changed = true;
        //conoutf(CON_DEBUG, "[3DVS-node-linker] linked parent %s with child %s.", from->node_name.c_str(), to->node_name.c_str());
    }

    // 
    void CVisualScriptSystem::disconnect_nodes(CScriptNode *from, CScriptNode *to)
    {
        // TODO: implement disconnect nodes!
    }

    // makes sure all the node's rules for linking are followed
    void CVisualScriptSystem::validate_new_relation(CScriptNode *from, CScriptNode *to)
    {
        if(nullptr != hovered_node)
        {
            // do not link nodes to itself!
            if(hovered_node != relation_start_node)
            {
                // check if nodes allow to be linked
                if(from->OnLinkAsParentNodeAttempt(to) && to->OnLinkAsChildNodeAttempt(from))
                {
                    connect_nodes(from, to);
                }
                else
                {
                    conoutf(CON_DEBUG, "[3DVS-node-linker] could not link parent %s with child %s.", from->node_name.c_str(), to->node_name.c_str());
                }
            }
            else
            {
                conoutf(CON_DEBUG,"[3DVS-node-linker] a node can't be linked to itself!");
            }
        }
    }

    void CVisualScriptSystem::update_input(int key, bool isdown)
    {
        // TODO: why the minus?
        switch( - key)
        {
            // left mouse button for dragging relations
            case SDL_BUTTON_LEFT:
            {
                if(!dragging_new_relation && isdown && !selection_blocked_by_geometry)
                {
                    // iterate through all nodes and check for box intersection
                    // TODO: store them and SORT by distance!
                    for(unsigned int i=0; i<nodes.size(); i++)
                    {
                        float dist = 0.0f;
                        int orient = INEXOR_VSCRIPT_BOX_NO_INTERSECTION;
                        vec p = nodes[i]->pos;

                        if(rayboxintersect(p, vec(boxsize), camera1->o, camdir, dist, orient))
                        {
                            // does this node allow relations to be dragged?
                            if(nodes[i]->OnRelationDragStart())
                            {
                                relation_drag_start = p;
                                relation_start_node = nodes[i];
                                dragging_new_relation = true;
                            }
                        }
                    }
                }
                if(dragging_new_relation && !isdown) // stop dragging
                {
                    // check if new relation should be formed
                    validate_new_relation(relation_start_node, hovered_node);
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
                        distance_calculated = false;
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
            if(INEXOR_VSCRIPT_NODE_TYPE_TIMER == nodes[i]->type) nodes[i]->reset();
        }
    }

    void CVisualScriptSystem::delete_all_nodes()
    {
        nodes.clear();
    }

    void CVisualScriptSystem::run()
    {
        for(unsigned int i = 0; i < nodes.size(); i++) nodes[i]->recursion_counter = 0;
        for(unsigned int i=0; i<nodes.size(); i++)
        {
            nodes[i]->this_time = SDL_GetTicks();
            switch(nodes[i]->type)
            {
                case INEXOR_VSCRIPT_NODE_TYPE_TIMER:
                case INEXOR_VSCRIPT_NODE_TYPE_EVENT:
                {
                    nodes[i]->in();
                    break;
                }
            }
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
            int orient = INEXOR_VSCRIPT_BOX_NO_INTERSECTION;

            rayboxintersect(nodes[i]->pos, vec(boxsize), camera1->o, camdir, dist, orient);
            nodes[i]->selected = (orient != INEXOR_VSCRIPT_BOX_NO_INTERSECTION);

            // make nodes blink when they have been triggered
            unsigned int color_effect_interval = 0;
            switch (nodes[i]->type)
            {
                case INEXOR_VSCRIPT_NODE_TYPE_TIMER:
                    // Because timers can have very low intervals we use a third of the timer's interval
                    // as the length of the color effect
                    color_effect_interval = static_cast<CTimerNode*>(nodes[i])->timer_interval / 3;
                    break;
                default:
                    color_effect_interval = INEXOR_VSCRIPT_NODE_ACTIVE_COLOR_EFFECT_INTERVAL;
                    break;
            }

            // render color effect
            if( (nodes[i]->this_time - nodes[i]->last_time) < color_effect_interval)
            {
                nodes[i]->box_color = nodes[i]->triggered_color;
            }
            else 
            {
                nodes[i]->box_color = nodes[i]->default_box_color;
            }

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
        gle::color(vec::hexcolor(INEXOR_VSCRIPT_COLOR_DEBUG_RAY));
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
                SNodeRelation *tmp = &nodes[i]->relations[e];

                // do we have to recompute the cache?
                if(nodes[i]->pos_changed || nodes[i]->children[e]->pos_changed)
                {
                    tmp->curve.ClearAllPoints();
            
                    // add additional interpolation data between the points
                    // to generate a nice and smooth curve
                    vec t = nodes[i]->pos;
                    vec n = nodes[i]->children[e]->pos;
                    vec interpol1 = vec(t.x, t.y, t.z - 40.0f);
                    vec interpol2 = vec(n.x, n.y, n.z + 40.0f);

                    t.x += boxsize/2;
                    t.y += boxsize/2;
                    n.x += boxsize/2;
                    n.y += boxsize/2;
                    n.z += boxsize;

                    tmp->curve.AddParameterPoint(t);
                    tmp->curve.AddParameterPoint(interpol1);
                    tmp->curve.AddParameterPoint(interpol2);
                    tmp->curve.AddParameterPoint(n);
                    
                    tmp->curve.ComputeCache();
                }

                glLineWidth(2.0f);
                glBegin(GL_LINES);

                // make nodes blink when they have been triggered
                unsigned int color_effect_interval = 0;
                switch (nodes[i]->type)
                {
                    case INEXOR_VSCRIPT_NODE_TYPE_TIMER:
                        // Because timers can have very low intervals we use a third of the timer's interval
                        // as the length of the color effect
                        color_effect_interval = static_cast<CTimerNode*>(nodes[i])->timer_interval / 3;
                        break;
                    default:
                        color_effect_interval = INEXOR_VSCRIPT_NODE_ACTIVE_COLOR_EFFECT_INTERVAL;
                        break;
                }

                // TODO: render all outgoing nodes in triggered colors

                // render color effect
                if((nodes[i]->this_time - nodes[i]->last_time) < color_effect_interval)
                {
                    gle::color(vec::hexcolor(INEXOR_VSCRIPT_COLOR_TRIGGERED));
                }
                else
                {
                    gle::color(vec::hexcolor(INEXOR_VSCRIPT_COLOR_WHITE));
                }

                for(unsigned int h=0; h<tmp->curve.GetCachedPointsSize() -1; h++)
                {
                    // render node relation curves "dotted"
                    if(h % 2 == 0) continue;
                    geom::SCustomOutputPoint t = tmp->curve.GetPoint_ByIndex(h);
                    geom::SCustomOutputPoint n = tmp->curve.GetPoint_ByIndex(h+1);
                    glVertex3f(t.pos.x, t.pos.y, t.pos.z);
                    glVertex3f(n.pos.x, n.pos.y, n.pos.z);
                }

                glEnd();
                glLineWidth(1.0f);
            }
        }
    }

    // TODO: declare new strategy for highlighting activated/triggered nodes!
    
    // TODO: force this stuff to work !!
    void CVisualScriptSystem::announce_event(INEXOR_VSCRIPT_EVENT_TYPE ev_type)
    {
        for(unsigned int i = 0; i < nodes.size(); i++)  nodes[i]->recursion_counter = 0;
        for(unsigned int i=0; i<nodes.size(); i++)
        {
            if(INEXOR_VSCRIPT_NODE_TYPE_EVENT == nodes[i]->type)
            {
                if(ev_type == static_cast<CEventBaseNode*>(nodes[i])->get_event_type())
                {
                    nodes[i]->this_time = SDL_GetTicks();
                    nodes[i]->in();
                }
            }
        }
    }


    void deleteallnodes()
    {
        vScript3D.delete_all_nodes();
        conoutf(CON_DEBUG, "[3DVS-nodes] removed all nodes and all node relations.");
    }
    COMMAND(deleteallnodes, "");
    
    // TODO: implement parameter validation!

    // timers
    void vs_timer(const char* interval)
    {
        vScript3D.add_node(INEXOR_VSCRIPT_NODE_TYPE_TIMER, 7, interval, "0", interval, "0", "timer1", "this is a comment", "0");
    }
    COMMAND(vs_timer, "s");


    // functions
    void vs_conoutf(const char* text)
    {
        vScript3D.add_node(INEXOR_VSCRIPT_NODE_TYPE_FUNCTION, 2, "0", text);
    }
    COMMAND(vs_conoutf,"s");


    // sleep
    void vs_sleep(const char *interval)
    {
        vScript3D.add_node(INEXOR_VSCRIPT_NODE_TYPE_SLEEP, 1, interval);
    }
    COMMAND(vs_sleep, "s");


    // comments
    void vs_comment(const char *comment)
    {
        vScript3D.add_node(INEXOR_VSCRIPT_NODE_TYPE_COMMENT, 1, comment);
    }
    COMMAND(vs_comment, "s");
    

    // areas
    void vs_box(const char* w, const char* h, const char* d)
    {
        vScript3D.add_node(INEXOR_VSCRIPT_NODE_TYPE_AREA_BOX, 3, w, h, d);
    }
    COMMAND(vs_box, "ssss");

    void vs_sphere(const char* radius)
    {
        vScript3D.add_node(INEXOR_VSCRIPT_NODE_TYPE_AREA_SPHERE, 1, radius);
    }
    COMMAND(vs_sphere, "s");

    void vs_cone(const char* height, const char* radius)
    {
        vScript3D.add_node(INEXOR_VSCRIPT_NODE_TYPE_AREA_CONE, 2, height, radius);
    }
    COMMAND(vs_cone, "ss");
    
    void vs_cylinder(const char* height, const char* radius)
    {
        vScript3D.add_node(INEXOR_VSCRIPT_NODE_TYPE_AREA_CYLINDER, 2, height, radius);
    }
    COMMAND(vs_cylinder, "ss");


    // operators
    void vs_increment(const char *value)
    {
        // increment is 0
        vScript3D.add_node(INEXOR_VSCRIPT_NODE_TYPE_OPERATOR, 2, "0", value);
    }
    COMMAND(vs_increment, "s");
    void vs_decrement(const char *value)
    {
        // decrement is 1
        vScript3D.add_node(INEXOR_VSCRIPT_NODE_TYPE_OPERATOR, 2, "1", value);
    }
    COMMAND(vs_decrement, "s");
    void vs_setnull(const char *value)
    {
        // set null is 2
        vScript3D.add_node(INEXOR_VSCRIPT_NODE_TYPE_OPERATOR, 2, "2", value);
    }
    COMMAND(vs_setnull, "s");


    // memory
    // integer values
    void vs_int(const char *value)
    {
        vScript3D.add_node(INEXOR_VSCRIPT_NODE_TYPE_MEMORY_INTEGER, 2, value, "0");
    }
    COMMAND(vs_int, "s");
    void vs_intconst(const char *value)
    {
        vScript3D.add_node(INEXOR_VSCRIPT_NODE_TYPE_MEMORY_INTEGER, 2, value, "1");
    }
    COMMAND(vs_intconst, "s");

    // float values
    void vs_float(const char *value)
    {
        vScript3D.add_node(INEXOR_VSCRIPT_NODE_TYPE_MEMORY_FLOAT, 2, value, "0");
    }
    COMMAND(vs_float, "s");
    void vs_floatconst(const char *value)
    {
        vScript3D.add_node(INEXOR_VSCRIPT_NODE_TYPE_MEMORY_FLOAT, 2, value, "1");
    }
    COMMAND(vs_floatconst, "s");
    
    // boolean values
    void vs_bool(const char *value)
    {
        vScript3D.add_node(INEXOR_VSCRIPT_NODE_TYPE_MEMORY_BOOL, 2, value, "0");
    }
    COMMAND(vs_bool, "s");
    void vs_boolconst(const char *value)
    {
        vScript3D.add_node(INEXOR_VSCRIPT_NODE_TYPE_MEMORY_BOOL, 2, value, "1");
    }
    COMMAND(vs_boolconst, "s");

    // conditional
    void vs_if(const char *value)
    {
        vScript3D.add_node(INEXOR_VSCRIPT_NODE_TYPE_IF, 2, value, "1");
    }
    COMMAND(vs_if, "s");


    // area events
    void vs_event(const char *value)
    {
        vScript3D.add_node(INEXOR_VSCRIPT_NODE_TYPE_EVENT, 1, value);
    }
    COMMAND(vs_event, "s");

};
};
