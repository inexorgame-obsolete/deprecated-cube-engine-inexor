/// @file fl_timer.hpp
/// @author Johannes Schneider
/// @brief implementation of dynamic script memory

#ifndef INEXOR_VSCRIPT_MEMBASE_HEADER
#define INEXOR_VSCRIPT_MEMBASE_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"

namespace inexor {
namespace vscript {


    enum VSCRIPT_DATA_TYPE 
    {
        VS_DATA_TYPE_INTEGER,
        VS_DATA_TYPE_FLOATING_POINT, // floating points are always double in this system
        VS_DATA_TYPE_STRING,
        VS_DATA_TYPE_BOOLEAN,
        VS_DATA_TYPE_VECTOR,
        VS_DATA_TYPE_TIMESTAMP,
        VS_DATA_TYPE_COLOR,
    };


    union VSCRIPT_MEMORY
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

        VSCRIPT_MEMORY data;
        VSCRIPT_DATA_TYPE type;
    };

    
    /// TODO: use std::any
    class CMemoryNode : public CScriptNode
    {
        public:

            CMemoryNode(vec position,
                        VSCRIPT_DATA_TYPE type,
                        const char* value,
                        const char* name,
                        const char* comment);

            ~CMemoryNode();

            SMemoryBlock block;

            /*
            void set(const char* raw_data, VSCRIPT_DATA_TYPE);

            void set_int(int value);
            void set_double(double value);
            void set_bool(bool value);

            int get_int();
            double get_double();
            bool get_bool();
            */
    };

};
};

#endif
