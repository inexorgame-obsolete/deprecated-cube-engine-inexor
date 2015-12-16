/// @file fl_nodebase.h
/// @author Johannes Schneider
/// @brief Basic implementation of nodes in Inexor's 3D Visual Scripting System

#ifndef INEXOR_VSCRIPT_NODEBASE_HEADER
#define INEXOR_VSCRIPT_NODEBASE_HEADER

#include <string>
#include <vector>
#include <map>
#include <list>

#include "inexor/geom/geom.h"
#include "inexor/flowgraph/renderer/fl_noderenderer.h"


namespace inexor {
namespace vscript {

    enum VSCRIPT_NODE_TYPE
    {
        NODE_TYPE_INVALID = -1,
        NODE_TYPE_TIMER = 0,
        NODE_TYPE_COMMENT,
        NODE_TYPE_FUNCTION,
        NODE_TYPE_MEMORY,
        NODE_TYPE_IF,
        NODE_TYPE_SWITCH,
        NODE_TYPE_CONDITION,
        NODE_TYPE_SLEEP,
    };


    class CScriptNode : public CNodeRenderer
    {
        public:

            VSCRIPT_NODE_TYPE type;

            CScriptNode();
            ~CScriptNode();

            std::vector<CScriptNode *> parents;
            std::vector<CScriptNode *> children;
            
            std::vector<inexor::geom::CBezierCurve> relations;

            vec pos;
            bool pos_changed;
            bool selected;

            std::string node_name;
            std::string node_comment;
            
            unsigned int this_time;
            unsigned int last_time;

            void in();
            //virtual void run() = 0;
            virtual void reset() = 0;
            void render(int, bool);
            void out();
    };

};
};

#endif
