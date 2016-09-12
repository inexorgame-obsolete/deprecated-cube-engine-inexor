/// @file fl_base.hpp
/// @author Johannes Schneider
/// @brief every script node is based on this basic node implementation.

#ifndef INEXOR_VSCRIPT_NODE_BASE_HEADER
#define INEXOR_VSCRIPT_NODE_BASE_HEADER

#include <string>
#include <vector>

#include "inexor/flowgraph/render/fl_render.hpp"
#include "inexor/geom/curves/bezier/bezier.hpp"

namespace inexor {
namespace vscript {

    #define INEXOR_VSCRIPT_NODE_ACTIVE_COLOR_EFFECT_INTERVAL 250
    #define INEXOR_VSCRIPT_DEFAULT_RENDER_DETAIL_LEVEL 50

    enum INEXOR_VSCRIPT_NODE_TYPE
    {
        INEXOR_VSCRIPT_NODE_TYPE_INVALID = -1,
        INEXOR_VSCRIPT_NODE_TYPE_COMMENT = 0,

        INEXOR_VSCRIPT_NODE_TYPE_TIMER,
        INEXOR_VSCRIPT_NODE_TYPE_EVENT,
        INEXOR_VSCRIPT_NODE_TYPE_FUNCTION,

        INEXOR_VSCRIPT_NODE_TYPE_MEMORY_INTEGER,
        INEXOR_VSCRIPT_NODE_TYPE_MEMORY_FLOAT,
        INEXOR_VSCRIPT_NODE_TYPE_MEMORY_BOOL,
        // TODO: implement more data types!

        INEXOR_VSCRIPT_NODE_TYPE_IF,
        INEXOR_VSCRIPT_NODE_TYPE_SWITCH,
        INEXOR_VSCRIPT_NODE_TYPE_CONDITION,
        INEXOR_VSCRIPT_NODE_TYPE_SLEEP,

        INEXOR_VSCRIPT_NODE_TYPE_AREA_BOX,
        INEXOR_VSCRIPT_NODE_TYPE_AREA_SPHERE,
        INEXOR_VSCRIPT_NODE_TYPE_AREA_CONE,
        INEXOR_VSCRIPT_NODE_TYPE_AREA_CYLINDER,

        INEXOR_VSCRIPT_NODE_TYPE_OPERATOR,
    };
    
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

            void set_name(const char*);
            void set_comment(const char*);

            virtual bool OnRelationDragStart();
            virtual bool OnRelationDragEnd();
            virtual bool OnLinkAsChildNodeAttempt(const CScriptNode*);
            virtual bool OnUnLinkAsChildNodeAttempt(const CScriptNode*);
            virtual bool OnLinkAsParentNodeAttempt(const CScriptNode*);
            virtual bool OnUnLinkAsParentNodeAttempt(const CScriptNode*);
            
            virtual void in();
            virtual void out();
            virtual void reset();

            virtual void render(int, bool);
            virtual void render_additional();

    };

};
};

#endif
