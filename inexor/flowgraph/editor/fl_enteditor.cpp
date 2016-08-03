#include "inexor/flowgraph/editor/fl_enteditor.hpp"

namespace inexor {
namespace vscript {

    CEntityManager::CEntityManager()
    {
        dragging_new_relation = false;
        last_mouse_key_state = false;
        moving_entity = false;
        relation_drag_start = vec(0,0,0);
        relation_drag_end = vec(0,0,0);
    }

    CEntityManager::~CEntityManager()
    {
    }

    void CEntityManager::update_mouse(int key, bool isdown)
    {
        if(key == - SDL_BUTTON_LEFT)
        {
            if(last_mouse_key_state != isdown) 
            {
                update_input(key, isdown);
                last_mouse_key_state = isdown;
            }
        }
        if(key == - SDL_BUTTON_RIGHT)
        {
            if(last_mouse_key_state != isdown) 
            {
                update_input(key, isdown);
                last_mouse_key_state = isdown;
            }
        }
    }

};
};
