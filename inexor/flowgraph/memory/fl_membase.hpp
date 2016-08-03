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
        INEXOR_VSCRIPT_DATA_TYPE_INTEGER,
        INEXOR_VSCRIPT_DATA_TYPE_FLOATING_POINT, // floating points are always double in this system
        INEXOR_VSCRIPT_DATA_TYPE_STRING,
        INEXOR_VSCRIPT_DATA_TYPE_BOOLEAN,
        INEXOR_VSCRIPT_DATA_TYPE_VECTOR,
        INEXOR_VSCRIPT_DATA_TYPE_TIMESTAMP,
        INEXOR_VSCRIPT_DATA_TYPE_COLOR,
    };

    union INEXOR_VSCRIPT_MEMORY
    {
        int    int_val;
        bool   bool_value;
        double double_value;
        char   str_value[1024];
    };

    struct SMemoryBlock
    {
        SMemoryBlock()
        {
        }

        ~SMemoryBlock()
        {
        }

        INEXOR_VSCRIPT_DATA_TYPE type;
        INEXOR_VSCRIPT_MEMORY data;
    };

    // TODO: use std::any
    class CMemoryNode : public CScriptNode
    {
        public:

            CMemoryNode();
            ~CMemoryNode();

            SMemoryBlock block;

            // Please note: I think you can't define virtual "get" methods or "set" methods in here because
            // this would require an explicit type such as   int get();

    };

};
};

#endif
