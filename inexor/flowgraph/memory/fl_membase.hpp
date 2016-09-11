/// @file fl_timer.hpp
/// @author Johannes Schneider
/// @brief implementation of dynamic script memory

#ifndef INEXOR_VSCRIPT_MEMBASE_HEADER
#define INEXOR_VSCRIPT_MEMBASE_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"

namespace inexor {
namespace vscript {

    // Please note: only integers and floating points can be incremented!
    enum INEXOR_VSCRIPT_DATA_TYPE 
    {
        INEXOR_VSCRIPT_DATA_TYPE_UNDEFINED = -1,
        INEXOR_VSCRIPT_DATA_TYPE_INTEGER = 0,
        INEXOR_VSCRIPT_DATA_TYPE_FLOATING_POINT, // floating points are always double in this system
        INEXOR_VSCRIPT_DATA_TYPE_STRING,
        INEXOR_VSCRIPT_DATA_TYPE_BOOLEAN,
        INEXOR_VSCRIPT_DATA_TYPE_VECTOR,
        INEXOR_VSCRIPT_DATA_TYPE_TIMESTAMP,
        INEXOR_VSCRIPT_DATA_TYPE_COLOR,
    };
    
    // TODO: ensure this memory size is available on all platforms!
    #define INEXOR_VSCRIPT_MEMORY_MAX_VALUE 1000 * 1000 * 1000

    union INEXOR_VSCRIPT_MEMORY
    {
        int    int_val;
        bool   bool_value;
        double double_value;
        char   str_value[8192];
    };

    struct SMemoryBlock
    {
        bool constant_value;
        INEXOR_VSCRIPT_DATA_TYPE type;
        INEXOR_VSCRIPT_MEMORY data;

        SMemoryBlock()
        {
            constant_value = false;
            type = INEXOR_VSCRIPT_DATA_TYPE_UNDEFINED;
        }

        ~SMemoryBlock()
        {
        }
    };

    // TODO: convert to std::any
    class CMemoryNode : public CScriptNode
    {
        public:

            CMemoryNode();
            ~CMemoryNode();

            SMemoryBlock block;

            bool CMemoryNode::OnLinkAsChildNodeAttempt(CScriptNode* parent);
            bool CMemoryNode::OnLinkAsParentNodeAttempt(CScriptNode* child);

        protected:

            std::string additional_particle_text;

            // Please note: I think you can't define virtual "get" methods or "set" methods in here because
            // this would require an explicit type such as "int get();"
    };

};
};

#endif
