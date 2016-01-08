/// @file fl_nodebase.h
/// @author Johannes Schneider
/// @brief Basic implementation of nodes in Inexor's 3D Visual Scripting System

#ifndef INEXOR_VSCRIPT_NODEBASE_HEADER
#define INEXOR_VSCRIPT_NODEBASE_HEADER

#include <string>
#include <vector>

#include "inexor/flowgraph/render/fl_render.hpp"
#include "inexor/geom/curves/bezier/bezier.hpp"


namespace inexor {
namespace vscript {

    enum VSCRIPT_NODE_TYPE
    {
        NODE_TYPE_INVALID = -1,
        NODE_TYPE_COMMENT = 0,

        // code executors
        NODE_TYPE_TIMER,
        NODE_TYPE_EVENT,

        // functions and memory
        NODE_TYPE_FUNCTION,
        NODE_TYPE_MEMORY,
        
        NODE_TYPE_IF,
        NODE_TYPE_SWITCH,
        NODE_TYPE_CONDITION,
        
        NODE_TYPE_SLEEP,

        // areas
        NODE_TYPE_AREA_BLOCK,
        NODE_TYPE_AREA_SPHERE,
        NODE_TYPE_AREA_CONE,
        NODE_TYPE_AREA_ZYLINDER,
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

            virtual void in() = 0;
            virtual void reset() = 0;
            //virtual void run() = 0;
            void render(int, bool);
            void out();
    };

};
};

#endif
