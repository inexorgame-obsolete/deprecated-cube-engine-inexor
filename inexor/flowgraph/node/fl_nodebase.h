/// @file fl_nodebase.h
/// @author Johannes Schneider
/// @brief Basic implementation of nodes in Inexor's 3D Visual Scripting System
/// 
/// .-------------------------------------------------------------------------------------------------.
/// | Basic node implementation                                                                       |
/// |_________________________________________________________________________________________________|
/// |                                                                                                 |
/// | Every node inherits its basic members and methods from this base class.                         |
/// | This base class manages the basic behaviour of nodes.                                           |
/// |_________________________________________________________________________________________________|
/// |                                                                                                 |
/// | The following members and methods will be inherited from every child class:                     |
/// |                                                                                                 |
/// | type          the type of the node (see VSCRIPT_NODE_TYPE enumeration).                         |
/// | selected      indicates if this node is selected by the editor. (TODO..)                        |
/// | pos           the position of the node in 3D space.                                             |
/// | active        indicates if this node is active for execution (TODO..)                           |
/// | node_name     a customizable name for this node. (TODO..)                                       |
/// | node_comment  a comment on this node. (TODO..)                                                  |
/// |                                                                                                 |
/// ._________________________________________________________________________________________________.
///

/// Please note: creating nodes with Sauerbraten's standard entity system does suck.
/// TODO: sooner or later the system will be rewritten based on Hanack's new entity system. 


#ifndef INEXOR_VSCRIPT_NODEBASE_HEADER
#define INEXOR_VSCRIPT_NODEBASE_HEADER

#include "inexor/engine/engine.h"

/// c++ standard libraries
#include <string>
#include <vector>
#include <map>
#include <list>


namespace inexor {
namespace vscript {

    /// The node entity's box size
    const float boxsize = 3.0f;

    /// enumeration of node types
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


    /// Enumeration of color codes in RGB integer format
    enum VSCRIPT_NODE_COLORS
    {
        VSCRIPT_COLOR_TIMER     = 0x00B6FF,
        VSCRIPT_COLOR_COMMENT   = 0x43A63A,
        VSCRIPT_COLOR_FUNCTION  = 0xCC47B1,    
        VSCRIPT_COLOR_TRIGGERED = 0xFF6D00,
        VSCRIPT_COLOR_GRAY      = 0xAAAAAA,
        VSCRIPT_COLOR_BLACK     = 0x000000,
    };

    /// @brief base class for node implementations
    class CScriptNode
    {
        public:

            VSCRIPT_NODE_TYPE type;

            /// TODO: What must be public and what can be private?
            std::vector<CScriptNode *> parents;
            std::vector<CScriptNode *> children;
        
            bool active;
            bool pos_changed;

            bool *done_pointer;
            CScriptNode* WhereDidWeStop;

            vec position;

            std::string node_name;
            std::string node_comment;

            bool selected;

            unsigned int this_time;
            unsigned int last_time;

            /// TODO: do we need this?
            int default_box_color;
            int box_color;

            unsigned long script_execution_start;

            CScriptNode();
            ~CScriptNode();

            void in();
            virtual void run() = 0; /// every child class implements this!
            void out();
            virtual void reset() = 0;
    };


/// end of namespaces
};
};

#endif
