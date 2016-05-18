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


    struct SNodeRelation
    {
        inexor::geom::CBezierCurve curve;
        bool triggered;

        SNodeRelation()
        {
            triggered = false;
        }

        ~SNodeRelation()
        {

        }

        // additional members here...
    };


    class CScriptNode : public CNodeRenderer
    {
        public:

            VSCRIPT_NODE_TYPE type;

            CScriptNode();
            ~CScriptNode();

            std::vector<CScriptNode *> parents;
            std::vector<CScriptNode *> children;
            
            std::vector<SNodeRelation> relations;

            vec pos;
            bool pos_changed;
            bool selected;
            bool triggered;

            std::string node_name;
            std::string node_comment;

            unsigned int this_time;
            unsigned int last_time;


            // The editor is trying to link/unlink it as child of another node
            virtual bool OnLinkAsChildNodeAttempt(CScriptNode* parent);
            virtual bool OnUnLinkAsChildNodeAttempt(CScriptNode* parent);

            // The editor is trying to link/unlink it as parent of another node
            virtual bool OnLinkAsParentNodeAttempt(CScriptNode* child);
            virtual bool OnUnLinkAsParentNodeAttempt(CScriptNode* child);
    

            virtual void in();
            virtual void out();
            virtual void reset();
            virtual void render(int, bool);
            virtual void render_additional(vec);

            virtual void trigger();
            virtual void untrigger();
    };

};
};

#endif
