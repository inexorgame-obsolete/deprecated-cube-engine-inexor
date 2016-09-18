/// @file fl_mem_float.hpp
/// @author Johannes Schneider
/// @brief implements floating point units.

#ifndef INEXOR_VSCRIPT_MEMORY_FLOAT_HEADER
#define INEXOR_VSCRIPT_MEMORY_FLOAT_HEADER

#include "inexor/flowgraph/memory/fl_membase.hpp"
#include "inexor/util/Logging.hpp"

namespace inexor {
namespace vscript {

    class CMemFloatNode : public CMemoryNode
    {
        public:
    
            CMemFloatNode(const vec, const bool, const bool, const int, const bool);
            ~CMemFloatNode();

            void increment();
            void decrement();

            void set_value(const double);
            double get_value();

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
