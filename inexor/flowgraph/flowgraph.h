/// @file flowgraph.h
/// @author Johannes Schneider
/// @brief 3D visual scripting system

/// include guard
#ifndef INEXOR_VSCRIPT_HEADER
#define INEXOR_VSCRIPT_HEADER

/// c++ standard libraries
#include <string>
#include <vector>
#include <map>
#include <list>

/// bezier curves
#include "inexor/geom/geom.h"
#include "inexor/engine/engine.h"

/// project's namespace protection
namespace inexor {
namespace vscript {

/// pre declarations
void node_render_test();
void notify_flowgraph_mouse_key_change(int, bool);
bool is_flowgraph_entity_selected();

/// enumeration of node types
enum VSCRIPT_NODE_TYPE
{
    NODE_TYPE_INVALID = -1,
    NODE_TYPE_TIMER = 0,
    NODE_TYPE_COMMENT,
};

/// data type enumeration
enum VSCRIPT_DATA_TYPE 
{
    TYPE_INTEGER_VALUE,  /// always signed
    TYPE_FLOATING_POINT, /// always double
    TYPE_STRING,
    TYPE_BOOLEAN,
    TYPE_VECTOR,
    TYPE_SYS_TIME,
    TYPE_COLOR,
    /// to be continued
};

/// box side selection indices
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

/// basic structure of entity
class script_node
{
    public:

    /// node type
    VSCRIPT_NODE_TYPE type;

    script_node() 
    {
        /// constructor sets standard value to invalid value
        type = NODE_TYPE_INVALID;
        active = true;       
        node_name = "";
        node_comment = "";        
        position = vec(0,0,0);
        /// TODO
        position_changed = false;
    }

    ~script_node() {}

    /// members that every node must have
    vec position;
    bool active;
    bool selected;
    
    bool position_changed;

    /// the name of this node
    //char node_name[256];
    std::string node_name;

    /// the comment for this node
    /// use comments whenever possible
    //char node_comment[1024];
    std::string node_comment;

    /// whatever this node does will be implemented here
    virtual void run() = 0;

    // TODO: ...
    /*
    virtual void enable();
    virtual void disable();
    virtual void remove();
    virtual void insert();
    */

    /// we need Hanacks entity system at this point
    /// relation with other nodes?

    /// all parents
    std::vector<script_node*> incoming;
    /// all children
    std::vector<script_node*> outgoing;

    /// this will be called when the node gets activated
    void input() {}
    /// decide which children will be called
    void output() {}
};


/// minimal time interval
#define INEXOR_VSCRIPT_MIN_TIMER_INTERVAL 20

/// maximum time interval
/// one day is the maximum delay
#define INEXOR_VSCRIPT_MAX_TIMER_INTERVAL 1000 * 60 * 60 * 24


/// timers are very easy objects
/// they do things in a delay of n miliseconds
/// and can have a start delay of x miliseconds
/// they can be active or inactive
class timer_node : public script_node
{
    public:

    /// overloaded constructor which passes timer interval
    timer_node(vec pos, unsigned int interval, unsigned int delay)
    {
        clamp(interval, INEXOR_VSCRIPT_MIN_TIMER_INTERVAL, INEXOR_VSCRIPT_MAX_TIMER_INTERVAL);
        position = pos;
        clock_interval = interval;
        start_delay = delay;
        last_time = SDL_GetTicks();
        activation_counter = 0;

        /// set the node's name
        node_name = "timer";

        /// set type
        type = NODE_TYPE_TIMER;
    }

    ~timer_node() {}

    /// timer related data
    /// time data in miliseconds
    unsigned int clock_interval;
    unsigned int start_delay;
    unsigned int last_time;
    unsigned int activation_counter;

    /// implementation of the run method
    /// which was declared as virtual in script_node
    void run()
    {
        /// set color to light blue
        glColor4f(0.0f, 148/255.0f, 1, 0.5);
        check_timer();
    }
    
    private:

    /// check the timer status
    /// do we need to call the trigger?
    void check_timer() 
    {
        unsigned int tmp = SDL_GetTicks();
        
        if(tmp - last_time >= clock_interval) 
        {
            /// trigger 
            trigger();
            /// save the timestamp
            last_time = SDL_GetTicks();
            /// increase activation counter
            activation_counter++;
        }

        /// yellow color effect is 100 ms long
        if(tmp - last_time < 100) glColor4f(1, 1, 0, 0.5);
    }

    /// event triggered
    void trigger()
    {
        //conoutf(CON_DEBUG, "trigger # %d", activation_counter);
        for(unsigned int i = 0; i < outgoing.size(); i++) {
            outgoing[i]->run();
        }
    }
};


/// this class represents comment in 3D space
/// a comment can not run code at all
class comment_node : public script_node
{
    public:

    /// overloaded standard constructor
    comment_node(vec pos, char* comment)
    {
        type = NODE_TYPE_COMMENT;
        position = pos;
        node_comment.copy(comment, strlen(comment));
        node_name.copy(comment, strlen(comment));
    }

    /// destructor has nothing to do (yet)
    ~comment_node() {}

    /// implementation of run
    /// there is no code a comment could run :)
    void run() {}
};


/// ray renderer shows your current camera position
/// and the position of your selection and renders
/// a ray.
class debug_ray
{
    public:
    vec pos;
    vec target;
};


/// @brief Visual Script System
class CVisualScriptSystem 
{
    private:

    /// the size of the quads which will be rendered as box
    /// around the target node's position
    const float boxsize = 4.0f;

    /// buffer for nodes
    std::vector<script_node *> nodes;
    /// buffer for debug rays
    std::vector<debug_ray> rays;

    /// change the color of the selected box side
    void adjust_selection_color(int, int);
    /// new rendering function based on collision box
    void renderbox(vec, int);

    void renderboxoutline(vec);

    void renderboxhelplines(vec);


    public:

    /// the selected node
    script_node* selected_node;

    /// entity selection?
    bool selected = false;

    CVisualScriptSystem();
    ~CVisualScriptSystem();

    /// add a node
    void add_node(char*,char*,char*,char*);
    /// render nodes
    void render_nodes();
    /// render relations
    void render_node_relations();
    /// render curves
    void render_bezier_curves();

    /// remove all nodes
    /// and relations
    void clear_nodes();

    /// TODO: change entity properties
    ///void change_property(propid ID, const char* val);
};

};
};

#endif /// INEXOR_VSCRIPT_HEADER
