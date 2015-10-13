#include "inexor/flowgraph/flowgraph.h"

/// selection information
extern selinfo sel, lastsel, savedsel;
/// editmode enabled or not?
extern bool editmode;
/// size of the grid selection
extern int gridsize;


/// protection namespace
namespace inexor {
namespace vscript {


/// constructor
CVisualScriptSystem::CVisualScriptSystem() 
{
}


/// garbage collection destructor
CVisualScriptSystem::~CVisualScriptSystem() 
{
    /// clear nodes dynamic memory in destructor
    /// @bug does that even work?
    /// @warning this garbage collection may causes touble?
    for(unsigned int i=0; i<nodes.size(); i++) {
        delete (nodes[i]);
    }
    nodes.clear();
}


/// TODO: debug!
#define INEXOR_VSCRIPT_ADDNODE_DEBUG
///#define INEXOR_VSCRIPT_DEBUG_RAYS


/// add a node to the system
/// @param type the type of the integer
/// problem: parameter specification requires new command line code!
/// we must get rid of this old 5 attributes stuff
/// this code has been debugged and tested
void CVisualScriptSystem::add_node(VSCRIPT_NODE_TYPE type, int parameter_count, ...)
{
    /// Calculate the target position of the node
    vec target = vec(sel.o.x,sel.o.y,sel.o.z);
    vec offset = vec(gridsize/2,gridsize/2,gridsize/2);
    target.add(offset);

    /// Add debug ray if neccesary
    #ifdef INEXOR_VSCRIPT_DEBUG_RAYS
        debug_ray dr_tmp;
        dr_tmp.pos = camera1->o;
        dr_tmp.target = target;
        rays.push_back(dr_tmp);
    #endif    

    /// Gather parameters
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

            INEXOR_VSCRIPT_TIMER_FORMAT timer_format;
            switch(atoi(arguments[6].c_str())) 
            {
                case 0: 
                    timer_format = TIMER_FORMAT_MILISECONDS;
                    break;
                case 1: 
                    timer_format = TIMER_FORMAT_SECONDS;
                    break;
                case 2: 
                    timer_format = TIMER_FORMAT_MINUTES;
                    break;
                case 3: 
                    timer_format = TIMER_FORMAT_HOURS;
                    break;
            }

            #ifdef INEXOR_VSCRIPT_ADDNODE_DEBUG
                conoutf(CON_DEBUG, "I added the following timer node: interval: %d, startdelay: %d, limit: %d, cooldown: %d, name: %s, comment: %s, type: %d", interval, startdelay, limit, cooldown, name, comment, timer_format);
            #endif

            /// Create a new timer
            nodes.push_back(new timer_node(target, interval, startdelay, limit, cooldown, name, comment, timer_format));
            break;
        }

        case NODE_TYPE_COMMENT:
        {
            /// TODO: does a comment have to have a name?
            nodes.push_back(new comment_node(target, arguments[0].c_str(), /*comment*/ 
                                                     arguments[1].c_str()  /*comment's name*/ ));
            break;
        }

        /// distinguish between functions
        case NODE_TYPE_FUNCTION:
        {
            switch(atoi(arguments[0].c_str()))
            {
                case FUNCTION_CONOUTF:
                    nodes.push_back(new function_conoutf_node(target, arguments[1].c_str()) );
                    break;    
            }
            break;
        }
    }
    /// TODO: garbage collection? dynamicly allocated memory must be released after use!
}

// TODO: Create an instance of a node/ray renderer
// and use it here!

/// render debug rays (test)
void CVisualScriptSystem::render_nodes()
{
    /// no node is selected in the beginning
    selected_node = nullptr;

    /// loop through all nodes and render them
    for(unsigned int i=0; i<nodes.size(); i++) 
    {
        /// render node box!
        float dist = 0.0f;
        int orient = VSCRIPT_BOX_NO_INTERSECTION;
        vec p = nodes[i]->position;

        /// check ray/box intersection
        rayboxintersect(p, vec(boxsize), camera1->o, camdir, dist, orient);

        /// this node is selected
        nodes[i]->selected = (orient != VSCRIPT_BOX_NO_INTERSECTION);

        /// render box as node representation
        gle::color(vec::hexcolor(nodes[i]->boxcolor));
        renderer.renderbox(p, orient, nodes[i]->boxcolor);

        /// no matter where the box is being selected, render help lines
        if(orient != VSCRIPT_BOX_NO_INTERSECTION) 
        {
            gle::color(vec::hexcolor(0xAAAAAA)); // gray
            renderer.renderboxhelplines(p);
        }
        
        /// render outline
        gle::color(vec::hexcolor(0x000000));
        renderer.renderboxoutline(p);

        /// render text above    
        p.add(vec(boxsize/2));
        p.add(vec(0,0,4));

        /// render node's name
        particle_text(p + vec(0,0,1.0f), nodes[i]->node_name.c_str(), PART_TEXT, 1, 0xFF009D, 1.0f);
        /// render node's comment
        particle_text(p, nodes[i]->node_comment.c_str(), PART_TEXT, 1, 0xFF009D, 1.0f);
    }

    /// which node is selected?
    for(unsigned int i=0; i<nodes.size(); i++)
    {
        if(nodes[i]->selected) selected_node = nodes[i];
    }
}

void CVisualScriptSystem::check_timers_and_events()
{
    /// If this is a node, run it!
    for(int i=0; i<nodes.size(); i++) 
    {
        if(NODE_TYPE_TIMER == nodes[i]->type) nodes[i]->run();
        /// TODO: if (NODE_TYPE_EVENT == nodes[i]->type) nodes[i]->run() ?;
    }
}

// TODO: connect nodes!
void CVisualScriptSystem::connect_nodes(script_node *from, script_node *to)
{
    /// TODO: relations?
    to->incoming.push_back(from);
    from->outgoing.push_back(to);

    /// TODO: add relation
    /// TODO: add bezier curve!
}


/// Synchronize timers
void CVisualScriptSystem::sync_timers()
{
    for(unsigned int i=0; i<nodes.size(); i++)
    {
        if(NODE_TYPE_TIMER == nodes[i]->type) nodes[i]->reset();
    }
}


// TODO: notify the node engine about mouse changes
void CVisualScriptSystem::mouse_event_notifyer(int code, bool isdown)
{
    /// Attention: we need that minus
    if(code == - SDL_BUTTON_LEFT) selected = isdown;
}


/// render relationships between nodes
void CVisualScriptSystem::render_node_relations()
{   
    /// this setup is required to render lines correctly
    //lineshader->set();
    
    /*
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    
    /// set color to spicy orange
    glColor3f(1.0f, 182/255.0f, 0.0f);

    /// render rays
    glBegin(GL_LINES);
    for(unsigned int i=0; i<rays.size(); i++) 
    {
        vec r=rays[i].pos, t=rays[i].target;
        glVertex3f(r.x,r.y,r.z);
        glVertex3f(t.x,t.y,t.z);
    }
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    */

    //defaultshader->set();
}


/// bezier curve as relations
void CVisualScriptSystem::render_bezier_curves()
{
    if(!nodes.size()) return;

    /*
    /// temporary curve instance
    inexor::geom::CBezierCurve tmp_curve;

    for(unsigned int i=0; i<nodes.size() -1; i++)
    {
        /// clear cache
        tmp_curve.ClearAllPoints();

        /// interpolation vector
        vec t=nodes[i]->position, n=nodes[i+1]->position;
        vec interpol = vec( (t.x+n.x)/2.0f, (t.y+n.y)/2.0f, (t.z+n.z)/2.0f - 30.0f);
        vec interpol2 = vec( (t.x+n.x)/2.0f, (t.y+n.y)/2.0f, (t.z+n.z)/2.0f + 30.0f);

        t.x += boxsize/2;
        t.y += boxsize/2;
        n.x += boxsize/2;
        n.y += boxsize/2;
        n.z += boxsize;

        /// this loop will always be abled to get access to the next node!
        /// beginning point
        tmp_curve.AddParamPoint(t);
        tmp_curve.AddParamPoint(interpol);
        tmp_curve.AddParamPoint(interpol2);
        tmp_curve.AddParamPoint(n);

        /// compute curve
        tmp_curve.PreComputeCache();

        /// render curve
        lineshader->set();
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
        glBegin(GL_LINES);

        /// set spicy orange color
        glColor3f(1.0f, 182/255.0f, 0.0f);

        /// render lines
        for(unsigned int h=0; h<tmp_curve.m_ComputedPoints.size() -1; h++)
        {
            vec t = tmp_curve.m_ComputedPoints[h], z = tmp_curve.m_ComputedPoints[h   +1];
            glVertex3f(t.x,t.y,t.z);
            glVertex3f(z.x,z.y,z.z);
        }
        glEnd();

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        defaultshader->set();
    }
    */
}


/// remove all nodes from visual scripting system
void CVisualScriptSystem::clear_nodes()
{
    nodes.clear();
    //rays.clear();
}


void CVisualScriptSystem::start_rendering()
{
    // TODO: What the fuck is this gle?
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


/// create instance of global 3D script enviroment system
CVisualScriptSystem vScript3D;


/// describes if a flowgraph entity is selected
bool is_flowgraph_entity_selected()
{
    if(vScript3D.selected) {
        if(nullptr != vScript3D.selected_node) return true;
    }
    return false;
}

/// remove all nodes
void deleteallnodes()
{
    vScript3D.clear_nodes();
}
COMMAND(deleteallnodes, "");



/*********************************************************************************************/

/// Linking the game with the node engine

/// prints a message to the screen
void addconoutf(char* message)
{
    /// TODO: debug!
    vScript3D.add_node(NODE_TYPE_FUNCTION, 2, "0" /* FUNCTION_CONOUTF */, message);
}
COMMAND(addconoutf, "s");


void addtimer(char* interval, char* startdelay, char* limit, char* cooldown, char* name, char* comment, char* timer_format)
{
    /// works fine (13.10.2015|18:19)
    vScript3D.add_node(NODE_TYPE_TIMER, 7, interval, startdelay, limit, cooldown, name, comment, timer_format);
}
COMMAND(addtimer, "sssssss");

void synctimers()
{
    vScript3D.sync_timers();
}
COMMAND(synctimers, "");


void addcomment(char* node_comment, char* node_name)
{
    /// works fine (13.10.2015|17:19)
    vScript3D.add_node(NODE_TYPE_COMMENT, 2, node_comment, node_name);
}
COMMAND(addcomment, "ss");


/// end of namespace
};
};
