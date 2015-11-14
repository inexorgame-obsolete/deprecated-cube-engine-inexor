/// @file enteditor.h
/// @author Johannes Schneider
/// @brief 3D Visual Scripting System's entity editor

#ifndef INEXOR_VSCRIPT_ENTITYMANAGER_HEADER
#define INEXOR_VSCRIPT_ENTITYMANAGER_HEADER

#include "inexor/engine/engine.h"
#include "inexor/flowgraph/node/fl_nodebase.h"

namespace inexor {
namespace vscript {

/// TOOD: move existing nodes!
/// TODO: create nodes

class CEntityManager
{
    public:

    CEntityManager();
    
    ~CEntityManager();

    /// the node which is currently selected
    script_node* selected_node;

    /// the node which is currently hovered
    script_node* hovered_node;

    void update_mouse(int, bool);

    //void update_camera_angle();

    void render_temp_connection();
    
    protected:

    /// TODO: drag only in XY, YZ, ZX axis
    /// TODO: drag only along 1 dimension (X,Y,Z)

    /// this vector describes the line from the camera
    /// to the entity in the moment of selection. it changes
    /// either with the position of the camera (new target pos += delta(campos));
    /// or the camera angles (yaw, pitch, but NOT roll!)
    /// TODO: math...
    vec dragging_target_pos_offset;

    vec drag_pos_start;
    vec drag_pos_current;

    vec camera_pos_start;
    vec camera_offset_start;
    vec camera_last_pos;
    
    bool old_isdown;

    bool dragging_new_relation;
    bool dragging_node;

    //void set_selected_node(script_node*);
    //void set_hovered_node(script_node*);

    /// Please note: we need to implement this later
    virtual void process_change(int, bool) = 0;

    //void drag();
    //void drop();
};

/// end of namespace
};
};

#endif
