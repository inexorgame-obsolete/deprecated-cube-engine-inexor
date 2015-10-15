#include "inexor/engine/engine.h"
#include "inexor/flowgraph/editor/fl_enteditor.h"

namespace inexor {
namespace vscript {

    CEntityManager::CEntityManager()
    {
        dragging_new_relation = false;
        dragging_node = false;
        selected_node = nullptr;
        hovered_node = nullptr;
    }


    CEntityManager::~CEntityManager()
    {
    }


    void CEntityManager::update_mouse(int key, bool isdown)
    {
        /// check if LEFT mouse button is down for dragging a connection out of the node
        if(key == - SDL_BUTTON_LEFT)
        {
            if(old_isdown != isdown) 
            {
                conoutf(CON_DEBUG, "left mouse changed");
                process_change(isdown);
                old_isdown = isdown;
            }
        }
        /// check if RIGHT mouse button is down for moving the entity
        if(key == - SDL_BUTTON_RIGHT)
        {
            if(old_isdown != isdown) 
            {
                conoutf(CON_DEBUG, "right mouse changed");
                process_change(isdown);
                old_isdown = isdown;
            }
        }
    }


    void CEntityManager::render(void)
    {
        if(dragging_node)
        {
        }
        
        /// TODO:
        if(dragging_new_relation)
        {
        }
    }


    void CEntityManager::process_change(bool isdown)
    {
        /*
        if(!isdown)
        {            
        }
        else 
        if(camera_ray_node_box_intersection)
        {
            set_selected_node();
            dragging = true;
        }
        */
    }

};
};
