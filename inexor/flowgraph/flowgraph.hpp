/// @file flowgraph.hpp
/// @author Johannes Schneider
/// @brief Inexor's Visual Scripting System

#ifndef INEXOR_VSCRIPT_FLOWGRAPH_HEADER
#define INEXOR_VSCRIPT_FLOWGRAPH_HEADER

#include <deque>
#include <vector>
#include <stdarg.h>

#include "inexor/flowgraph/nodebase/fl_base.hpp"
#include "inexor/flowgraph/render/fl_render.hpp"
#include "inexor/flowgraph/editor/fl_enteditor.hpp"
#include "inexor/flowgraph/debugger/fl_dbgrays.hpp"
#include "inexor/flowgraph/events/base/fl_event_base.hpp"
#include "inexor/util/Logging.hpp"

namespace inexor {
namespace vscript {

    class CVisualScriptSystem : public CEntityManager
    {
        protected:

            void update_input(int, bool);
            bool distance_calculated;

        public:        

            CVisualScriptSystem();
            ~CVisualScriptSystem();

            std::vector<CScriptNode*> nodes;
            std::vector<SNodeRelation> relations;
            
            std::vector<CDebugRay> rays;

            inexor::math::curves::CBezierCurve tmp_relation_linker_curve;

            CScriptNode* add_node(INEXOR_VSCRIPT_NODE_TYPE, int, ...);
            void remove_node(CScriptNode*);

            void start_rendering();
            void end_rendering();

            void render_nodes();
            void render_node_relations();
            void render_debug_rays();

            void run();
            
            void validate_new_relation(CScriptNode *, CScriptNode *);

            void connect_nodes(CScriptNode *, CScriptNode *);
            void disconnect_nodes(CScriptNode *, CScriptNode *);

            void announce_event(INEXOR_VSCRIPT_EVENT_TYPE);

            void update_drag_n_drop();
            void update_relation_linker();

            void sync_all_timers();
            void delete_all_nodes();
    };

    // extern CVisualScriptSystem vScript3D;

};
};

#endif
