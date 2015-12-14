/// @file fl_nodebase.h
/// @author Johannes Schneider
/// @brief Basic implementation of nodes in Inexor's 3D Visual Scripting System

#ifndef INEXOR_VSCRIPT_NODEBASE_HEADER
#define INEXOR_VSCRIPT_NODEBASE_HEADER

#include <string>
#include <vector>
#include <map>
#include <list>



namespace inexor {
namespace vscript {

    #include "inexor/geom/geom.h"

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
        VSCRIPT_COLOR_TIMER     = 0x00B6FF,
        VSCRIPT_COLOR_COMMENT   = 0x43A63A,
        VSCRIPT_COLOR_FUNCTION  = 0xCC47B1,
        VSCRIPT_COLOR_TRIGGERED = 0xFF6D00,
        VSCRIPT_COLOR_SLEEP     = 0xFF00CD,
        VSCRIPT_COLOR_GRAY      = 0xAAAAAA,
        VSCRIPT_COLOR_BLACK     = 0x000000,
        VSCRIPT_COLOR_WHITE     = 0xFFFFFF,
        VSCRIPT_COLOR_SELECTION = 0xFF5900,
    };


    class CScriptNode
    {
        public:

            CScriptNode();
            ~CScriptNode();

            vec pos;
            VSCRIPT_NODE_TYPE type;

            std::vector<CScriptNode *> parents;
            std::vector<CScriptNode *> children;

            std::vector<CBezierCurve> relation_curves;

            bool active;
            bool pos_changed;
            bool *done_pointer;

            std::string node_name;
            std::string node_comment;

            bool selected;

            unsigned int this_time;
            unsigned int last_time;

            int default_box_color;
            int box_color;

            unsigned long script_execution_start;

            void in();
            virtual void run() = 0;
            virtual void reset() = 0;
            void out();
    };

};
};

#endif
