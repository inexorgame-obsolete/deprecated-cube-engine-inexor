/// @file fl_timer.hpp
/// @author Johannes Schneider
/// @brief implements integer nodes (whole numbers).

#ifndef INEXOR_VSCRIPT_MEMORY_INTEGER_HEADER
#define INEXOR_VSCRIPT_MEMORY_INTEGER_HEADER

#include "inexor/flowgraph/memory/fl_membase.hpp"

// TODO: ensure this memory size is available on all platforms!
#define INEXOR_VSCRIPT_MEMORY_MAX_VALUE 1000 * 1000 * 1000

namespace inexor {
namespace vscript {

    class CMemIntegerNode : public CMemoryNode
    {
        public:
    
            CMemIntegerNode(vec, bool, bool, int);
            ~CMemIntegerNode();

            void increment();
            void decrement();

            void set_value(int);
            int  get_value();
            
            void render_additional();

            //virtual bool OnLinkAsChildNodeAttempt(CScriptNode* parent);
            //virtual bool OnUnLinkAsChildNodeAttempt(CScriptNode* parent);
            //virtual bool OnLinkAsParentNodeAttempt(CScriptNode* child);
            //virtual bool OnUnLinkAsParentNodeAttempt(CScriptNode* child);

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
