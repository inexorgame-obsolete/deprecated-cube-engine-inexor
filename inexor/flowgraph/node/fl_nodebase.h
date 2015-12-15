/// @file fl_nodebase.h
/// @author Johannes Schneider
/// @brief Basic implementation of nodes in Inexor's 3D Visual Scripting System

#ifndef INEXOR_VSCRIPT_NODEBASE_HEADER
#define INEXOR_VSCRIPT_NODEBASE_HEADER

#include <string>
#include <vector>
#include <map>
#include <list>

#include "inexor/engine/engine.h"

#include "inexor/geom/curves/bezier/bezier.h"


namespace inexor {
namespace vscript {

    const float boxsize = 4.0f;

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

    enum VSCRIPT_NODE_COLORS
    {
        VSCRIPT_COLOR_TIMER     = 0x51ABCC,  // light blue
        VSCRIPT_COLOR_COMMENT   = 0x5BCC51,  // comment green
        VSCRIPT_COLOR_FUNCTION  = 0x51ABCC,  // darker purple
        VSCRIPT_COLOR_TRIGGERED = 0xFF8800,  // spicy orange
        VSCRIPT_COLOR_SLEEP     = 0x51ABCC,  
        VSCRIPT_COLOR_GRAY      = 0xAAAAAA,  // 
        VSCRIPT_COLOR_BLACK     = 0x000000,  // 
        VSCRIPT_COLOR_WHITE     = 0xFFFFFF,  // 
        VSCRIPT_COLOR_SELECTION = 0xFFFF4C,  // red 
        VSCRIPT_COLOR_DEBUG_RAY = 0x51ABCC,
    };


    class CScriptNode
    {
        public:

            CScriptNode();
            ~CScriptNode();

            std::vector<CScriptNode *> parents;
            std::vector<CScriptNode *> children;
            
            std::vector<inexor::geom::CBezierCurve> relations;

            vec pos;
            bool pos_changed;
            bool selected;
            VSCRIPT_NODE_TYPE type;

            std::string node_name;
            std::string node_comment;
            
            unsigned int this_time;
            unsigned int last_time;

            VSCRIPT_NODE_COLORS default_box_color;
            VSCRIPT_NODE_COLORS box_color;

            void in();
            virtual void run() = 0;
            virtual void reset() = 0;
            void out();
    };

};
};

#endif
