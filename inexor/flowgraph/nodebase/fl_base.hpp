/// @file fl_base.hpp
/// @author Johannes Schneider
/// @brief a basic implementation of nodes in Inexor's Visual Scripting System

#ifndef INEXOR_VSCRIPT_NODEBASE_HEADER
#define INEXOR_VSCRIPT_NODEBASE_HEADER

#include <string>
#include <vector>

#include "inexor/flowgraph/render/fl_render.hpp"
#include "inexor/geom/curves/bezier/bezier.hpp"

#define INEXOR_VSCRIPT_NODE_ACTIVE_COLOR_EFFECT_INTERVAL 200 

namespace inexor {
namespace vscript {

    enum INEXOR_VSCRIPT_NODE_TYPE
    {
        INEXOR_VSCRIPT_NODE_TYPE_INVALID = -1,
        INEXOR_VSCRIPT_NODE_TYPE_COMMENT = 0,
        
        // these nodes can start a code execution
        INEXOR_VSCRIPT_NODE_TYPE_TIMER,
        INEXOR_VSCRIPT_NODE_TYPE_EVENT,
        INEXOR_VSCRIPT_NODE_TYPE_FUNCTION,
        
        //INEXOR_VSCRIPT_NODE_TYPE_MEMORY,
        INEXOR_VSCRIPT_NODE_TYPE_MEMORY_INTEGER,
        INEXOR_VSCRIPT_NODE_TYPE_MEMORY_FLOAT,
        INEXOR_VSCRIPT_NODE_TYPE_MEMORY_BOOL,

        // TODO: list and implement more data types
        INEXOR_VSCRIPT_NODE_TYPE_IF,
        INEXOR_VSCRIPT_NODE_TYPE_SWITCH,
        INEXOR_VSCRIPT_NODE_TYPE_CONDITION,
        INEXOR_VSCRIPT_NODE_TYPE_SLEEP,

        // area definitions
        INEXOR_VSCRIPT_NODE_TYPE_AREA_BOX,
        INEXOR_VSCRIPT_NODE_TYPE_AREA_SPHERE,
        INEXOR_VSCRIPT_NODE_TYPE_AREA_CONE,
        INEXOR_VSCRIPT_NODE_TYPE_AREA_CYLINDER,

        // operators
        INEXOR_VSCRIPT_NODE_TYPE_OPERATOR,
    };

    enum INEXOR_VSCRIPT_OPERATOR_TYPE
    {
        INEXOR_VSCRIPT_OPERATOR_TYPE_INCREMENT = 0,
        INEXOR_VSCRIPT_OPERATOR_TYPE_DECREMENT,
        INEXOR_VSCRIPT_OPERATOR_TYPE_SETNULL,
        INEXOR_VSCRIPT_OPERATOR_TYPE_SETVAL,
    };

    // TODO: implement areas that can be rotated in 3 dimensions

    class CScriptNode;

    struct SNodeRelation
    {
        SNodeRelation();
        ~SNodeRelation();

        CScriptNode* from;
        CScriptNode* to;

        inexor::geom::CBezierCurve curve;
    };

    class CScriptNode : public CNodeRenderer
    {
        public:

            CScriptNode();
            ~CScriptNode();

            void set_name(const char*);
            void set_comment(const char*);

            vec pos;
            INEXOR_VSCRIPT_NODE_TYPE type;

            bool pos_changed;
            bool selected;
            bool triggered;

            unsigned int this_time;
            unsigned int last_time;
            unsigned int recursion_counter;

            std::string node_name;
            std::string node_comment;

            std::vector<CScriptNode*> parents;
            std::vector<CScriptNode*> children;
            std::vector<SNodeRelation> relations;

            // events will always be triggered, but event handling depends on the node type.
            // some node types will not allow certain events.
            // "comment" nodes e.g. can't have any node relation with other nodes.
            virtual bool OnRelationDragStart();
            virtual bool OnRelationDragEnd();

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
