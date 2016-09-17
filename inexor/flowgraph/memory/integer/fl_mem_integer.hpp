/// @file fl_timer.hpp
/// @author Johannes Schneider
/// @brief implements integer nodes (whole numbers).

#ifndef INEXOR_VSCRIPT_MEMORY_INTEGER_HEADER
#define INEXOR_VSCRIPT_MEMORY_INTEGER_HEADER

#include "inexor/flowgraph/memory/fl_membase.hpp"

namespace inexor {
namespace vscript {

    class CMemIntegerNode : public CMemoryNode
    {
        public:
    
            CMemIntegerNode(const vec, const bool, const bool, const int, const bool);
            ~CMemIntegerNode();

            void increment();
            void decrement();

            void set_value(const int);
            int  get_value();
            
            // render the current integer value
            void render_additional();
            
        protected:
         
            bool can_be_null = true;
            bool can_be_negative = true;

            /// boundaries for integer values
            int minimal_value = - INEXOR_VSCRIPT_MEMORY_MAX_VALUE;
            int maximal_value = + INEXOR_VSCRIPT_MEMORY_MAX_VALUE;

    };

};
};

#endif
