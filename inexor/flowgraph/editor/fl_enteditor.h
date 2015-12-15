/// @file fl_enteditor.h
/// @author Johannes Schneider
/// @brief 3D Visual Scripting System's entity editor

#ifndef INEXOR_VSCRIPT_ENTITYMANAGER_HEADER
#define INEXOR_VSCRIPT_ENTITYMANAGER_HEADER

#include "inexor/engine/engine.h"
#include "inexor/flowgraph/node/fl_nodebase.h"


namespace inexor {
namespace vscript {

    class CEntityManager
    {
        protected:

            bool dragging_node;
            bool dragging_new_relation;

            bool last_mouse_key_state;

            //vec drag_pos_current;
            //vec drag_pos_start;

            vec move_pos_start;
            vec node_pos_start;

            bool moving_entity;

            virtual void process_change(int, bool) = 0;

        public:

            bool selection_blocked_by_geometry;

            CEntityManager();
            ~CEntityManager();

            CScriptNode* selected_node;
            CScriptNode* hovered_node;

            void update_mouse(int, bool);
    };

};
};

#endif
