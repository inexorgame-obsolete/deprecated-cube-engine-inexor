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
    
            CMemIntegerNode(vec, bool, bool, int, bool);
            ~CMemIntegerNode();

            void increment();
            void decrement();

            void set_value(int);
            int  get_value();
            
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
