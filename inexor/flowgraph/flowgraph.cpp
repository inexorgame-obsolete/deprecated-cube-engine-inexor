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


/// add a node to the system
/// @param type the type of the integer
/// problem: parameter specification requires new command line code!
/// we must get rid of this old 5 attributes stuff
/// this code has been debugged and tested
void CVisualScriptSystem::add_node(char* a, char* b, char* c, char* d)
{
    /// get the target vector
    vec node_target_position = vec(sel.o.x,sel.o.y,sel.o.z);
    vec current_player_position = camera1->o;

    vec offset = vec(gridsize/2,gridsize/2,gridsize/2);
    node_target_position.add(offset);

    /// create ray
    debug_ray dr_tmp;
    dr_tmp.pos = current_player_position;
    dr_tmp.target = node_target_position;
    //rays.push_back(dr_tmp);
    
    int type = atoi(a);

    /// TODO: garbage collection ???
    /// dynamicly allocated memory must be released after use!

    /// add new content depending on the type
    switch(type)
    {
        /// timer: show block
        case NODE_TYPE_TIMER:
        {
            nodes.push_back(new timer_node(node_target_position,atoi(b),atoi(c)));
            break;
        }
        /// comment: render its text
        case NODE_TYPE_COMMENT:
        {
            nodes.push_back(new comment_node(node_target_position, b));
            break;
        }
    }
}


// TODO: Create an instance of a node/ray renderer
// and use it here!

/// render debug rays (test)
void CVisualScriptSystem::render_nodes()
{
    /// this setup is required to render lines correctly
    //lineshader->set();
    /// shaders: nullshader hudshader hudnotextureshader textureshader notextureshader nocolorshader foggedshader foggednotextureshader stdworldshader
    // TODO: does this work?
    nocolorshader->set();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    /// TODO: is this legal?
    selected_node = nullptr;

    /// loop through all nodes and render them
    for(unsigned int i=0; i<nodes.size(); i++) 
    {
        /// run node code!
        nodes[i]->run();

        /// render node box!
        float dist = 0.0f;
        int orient = VSCRIPT_BOX_NO_INTERSECTION;
        vec p = nodes[i]->position;

        /// check ray/box intersection
        rayboxintersect(p, vec(boxsize), camera1->o, camdir, dist, orient);

        /// this node is selected
        nodes[i]->selected = (orient != VSCRIPT_BOX_NO_INTERSECTION);

        /// render entity
        renderbox(p, orient);

        /// no matter where the box is being selected, render help lines
        if(orient != VSCRIPT_BOX_NO_INTERSECTION)
        {
            glColor3f(0.5f,0.5f,0.5f);
            renderboxhelplines(p);
        }

        renderboxoutline(p);

        /// render text above    
        p.add(vec(boxsize/2));
        p.add(vec(0,0,4));
        particle_text(p, nodes[i]->node_name.c_str(), PART_TEXT, 20000, 0xFF47E6, 2.0f);
    }

    /// which node is selected?
    for(unsigned int i=0; i<nodes.size(); i++)
    {
        if(nodes[i]->selected) {
            selected_node = nodes[i];
        }
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    stdworldshader->set();
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




/// create instance of global 3D script enviroment system
CVisualScriptSystem vScript3D;

/// render nodes!
void node_render_test()
{
    vScript3D.render_nodes();
    vScript3D.render_node_relations();
    vScript3D.render_bezier_curves();

    
    /// only show nodes in editmode
    if(editmode)
    {
        /// move code block in here later on
    }
}

/// mouse button notifyer
void notify_flowgraph_mouse_key_change(int key, bool isdown)
{
    /// we need that minus
    if(key == -SDL_BUTTON_LEFT) vScript3D.selected = isdown;
}

/// describes if a flowgraph entity is selected
bool is_flowgraph_entity_selected()
{
    if(vScript3D.selected) {
        if(nullptr != vScript3D.selected_node) return true;
    }
    return false;
}

/// add a new node
void addnode(char* a, char* b, char* c, char* d)
{
    vScript3D.add_node( a,b,c,d );
}
COMMAND(addnode, "ssss");

/// remove all nodes
void deleteallnodes()
{
    vScript3D.clear_nodes();
}
COMMAND(deleteallnodes, "");

};
};
