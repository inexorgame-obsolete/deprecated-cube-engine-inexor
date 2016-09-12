/// @file fl_mem_bool.hpp
/// @author Johannes Schneider
/// @brief implements boolean values.

#ifndef INEXOR_VSCRIPT_MEMORY_BOOL_HEADER
#define INEXOR_VSCRIPT_MEMORY_BOOL_HEADER

#include "inexor/flowgraph/memory/fl_membase.hpp"

namespace inexor {
namespace vscript {

    class CMemBoolNode : public CMemoryNode
    {
        public:
    
            CMemBoolNode(vec, bool, bool);
            ~CMemBoolNode();

            void set_value(bool);
            bool get_value();
            
            // render the current status (true or false)
            void render_additional();
            
    };

};
};

#endif
