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
            /// TODO: drag only in XY, YZ, ZX axis
            /// TODO: drag only along 1 dimension (X,Y,Z)

            /// this vector describes the line from the camera
            /// to the entity in the moment of selection. it changes
            /// either with the position of the camera (new target pos += delta(campos));
            /// or the camera angles (yaw, pitch, but NOT roll!)
            vec dragging_target_pos_offset;

            vec drag_pos_start;
            vec drag_pos_current;

            vec camera_pos_start;
            vec camera_offset_start;
            vec camera_last_pos;
    
            bool old_isdown;

            bool dragging_new_relation;
            bool dragging_node;

            /// TODO
            virtual void process_change(int, bool) = 0;

        public:

            CEntityManager();
            ~CEntityManager();

            CScriptNode* selected_node;
            CScriptNode* hovered_node;

            void update_mouse(int, bool);
            void render_temp_connection();
    
    };

};
};

#endif
