/// @file fl_mem_float.hpp
/// @author Johannes Schneider
/// @brief implements floating point units.

#ifndef INEXOR_VSCRIPT_MEMORY_FLOAT_HEADER
#define INEXOR_VSCRIPT_MEMORY_FLOAT_HEADER

#include "inexor/flowgraph/memory/fl_membase.hpp"

// TODO: ensure this memory size is available on all platforms!
#define INEXOR_VSCRIPT_MEMORY_MAX_VALUE 1000 * 1000 * 1000

namespace inexor {
namespace vscript {

    class CMemFloatNode : public CMemoryNode
    {
        public:
    
            CMemFloatNode(vec, bool, bool, int, const char*, const char*);
            ~CMemFloatNode();

            void increment();
            void decrement();

            void set_value(double);
            double get_value();
            
            void render_additional();
            
        protected:

            /// some useful native options for integer values            
            bool can_be_null = true;
            /// signed or not?
            bool can_be_negative = true;
            /// boundaries for integer values
            int minimal_value = - INEXOR_VSCRIPT_MEMORY_MAX_VALUE;
            int maximal_value = + INEXOR_VSCRIPT_MEMORY_MAX_VALUE;

            std::string additional_particle_text;
    };

};
};

#endif
