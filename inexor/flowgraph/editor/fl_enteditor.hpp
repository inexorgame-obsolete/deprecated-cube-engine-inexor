/// @file fl_enteditor.hpp
/// @author Johannes Schneider
/// @brief 3D Inexor's Visual Scripting System's entity editor

#ifndef INEXOR_VSCRIPT_ENTITYMANAGER_HEADER
#define INEXOR_VSCRIPT_ENTITYMANAGER_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"

namespace inexor {
namespace vscript {

    class CEntityManager
    {
        public:

            CEntityManager();
            ~CEntityManager();

            CScriptNode* selected_node;
            CScriptNode* hovered_node;
            CScriptNode* relation_start_node;

            bool last_mouse_key_state;
            bool selection_blocked_by_geometry;
            bool moving_entity;
            bool dragging_new_relation;

            vec relation_drag_start;
            vec relation_drag_end;

            virtual void update_input(int, bool) = 0;

            void update_mouse(int key, bool isdown);
    };

};
};

#endif
