#include "inexor/flowgraph/memory/integer/fl_mem_integer.hpp"

namespace inexor {
namespace vscript {

    CMemIntegerNode::CMemIntegerNode(vec position, bool null_allowed, bool negative_allowed, 
                                     int value, const char* name, const char* comment = "")
    {
        type = INEXOR_VSCRIPT_NODE_TYPE_MEMORY_INTEGER;
        pos = position;
        node_name = name;
        node_comment = comment;
        
        //can_be_null = null_allowed;
        //can_be_negative = negative_allowed;

        block.type = INEXOR_VSCRIPT_DATA_TYPE_INTEGER;
        block.data.int_val = value;
    }

    CMemIntegerNode::~CMemIntegerNode()
    {
    }

    void CMemIntegerNode::render_additional()
    {
        // render the current integer value
        vec p = pos;
        p.add(vec(boxsize/2));
        p.add(vec(0,0,4));
        // this is a great C++11 feature!
        additional_particle_text = std::to_string(block.data.int_val);
        particle_text(p + vec(0,0,2.0f), additional_particle_text.c_str(), PART_TEXT, 1, INEXOR_VSCRIPT_COLOR_TRIGGERED, 1.0f);
    }

    void CMemIntegerNode::increment()
    {
        block.data.int_val++;
    }

    void CMemIntegerNode::decrement()
    {
        block.data.int_val--;
    }

    void CMemIntegerNode::set_value(int set_value)
    {
        block.data.int_val = set_value;
    }

    int CMemIntegerNode::get_value()
    {
        return block.data.int_val;
    }

};
};