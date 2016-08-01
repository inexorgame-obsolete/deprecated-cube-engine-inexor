/// @file fl_base.hpp
/// @author Johannes Schneider
/// @brief a basic implementation of nodes in Inexor's Visual Scripting System

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
        // these nodes can start a code execution
        NODE_TYPE_TIMER,
        NODE_TYPE_EVENT,
        // functions and memory
        NODE_TYPE_FUNCTION,
        NODE_TYPE_MEMORY,
        
        NODE_TYPE_IF,
        NODE_TYPE_SWITCH,
        NODE_TYPE_CONDITION,
        NODE_TYPE_SLEEP,
        // area definitions
        NODE_TYPE_AREA_BOX,
        NODE_TYPE_AREA_SPHERE,
        NODE_TYPE_AREA_CONE,
        NODE_TYPE_AREA_ZYLINDER,
        //NODE_TYPE_PYRAMID,
        //NODE_TYPE_POLYGON,
        //NODE_TYPE_TUBE,
    };

    // TODO: implement areas that can be rotated in 3 dimensions

    struct SNodeRelation
    {
        SNodeRelation();
        ~SNodeRelation();

        inexor::geom::CBezierCurve curve;
        bool triggered;
    };


    class CScriptNode : public CNodeRenderer
    {
        public:

            CScriptNode();
            ~CScriptNode();

            vec pos;
            VSCRIPT_NODE_TYPE type;

            bool pos_changed;
            bool selected;
            bool triggered;

            unsigned int this_time;
            unsigned int last_time;

            std::string node_name;
            std::string node_comment;

            std::vector<CScriptNode*> parents;
            std::vector<CScriptNode*> children;
            std::vector<SNodeRelation> relations;

            // events will always be triggered, but event handling depends on the node type.
            // some node types will not allow certain events.
            // "comment" nodes e.g. can't have any node relation with other nodes.

            virtual bool OnRelationDragStart();
            // the user is trying to link/unlink the node as CHILD of another node
            virtual bool OnLinkAsChildNodeAttempt(CScriptNode* parent);
            virtual bool OnUnLinkAsChildNodeAttempt(CScriptNode* parent);
            // the editor is trying to link/unlink it as PARENT of another node
            virtual bool OnLinkAsParentNodeAttempt(CScriptNode* child);
            virtual bool OnUnLinkAsParentNodeAttempt(CScriptNode* child);
            
            virtual void in();
            virtual void out();
            virtual void reset();

            virtual void render(int, bool);
            virtual void render_additional();

    };

};
};

#endif
