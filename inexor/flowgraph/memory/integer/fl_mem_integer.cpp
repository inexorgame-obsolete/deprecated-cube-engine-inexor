#include "inexor/flowgraph/memory/integer/fl_mem_integer.hpp"

namespace inexor {
namespace vscript {

    CMemIntegerNode::CMemIntegerNode(vec position, bool null_allowed, bool negative_allowed, int value, bool const_value)
    {
        type = INEXOR_VSCRIPT_NODE_TYPE_MEMORY_INTEGER;
        pos = position;
        block.type = INEXOR_VSCRIPT_DATA_TYPE_INTEGER;
        block.data.int_val = value;
        block.constant_value = const_value;
    }

    CMemIntegerNode::~CMemIntegerNode()
    {
    }


    void CMemIntegerNode::render_additional()
    {
        vec p = pos;
        p.add(vec(boxsize/2));
        p.add(vec(0,0,4));
        additional_particle_text = std::to_string(block.data.int_val);
        particle_text(p + vec(0,0,2.0f), additional_particle_text.c_str(), PART_TEXT, 1, INEXOR_VSCRIPT_COLOR_TRIGGERED, 1.0f);
        if(block.constant_value)
        {
            particle_text(p + vec(0,0,3.0f), "constant value", PART_TEXT, 1, INEXOR_VSCRIPT_COLOR_PENDING, 1.0f);
        }
    }

    void CMemIntegerNode::increment()
    {
        last_time = this_time;
        if(block.constant_value)
        {
            triggered_color = INEXOR_VSCRIPT_COLOR_PENDING;
            conoutf(CON_DEBUG, "[3DVS-int-increment] can't increment a constant integer value!");
        }
        else block.data.int_val ++;
    }

    void CMemIntegerNode::decrement()
    {
        last_time = this_time;
        if(block.constant_value)
        {
            triggered_color = INEXOR_VSCRIPT_COLOR_PENDING;
            conoutf(CON_DEBUG, "[3DVS-int-decrement] can't decrement a constant integer value!");
        }
        else block.data.int_val --;
    }

    void CMemIntegerNode::set_value(int set_value)
    {
        last_time = this_time;
        if(block.constant_value)
        {
            triggered_color = INEXOR_VSCRIPT_COLOR_PENDING;
            conoutf(CON_DEBUG, "[3DVS-int-setvalue] can't change constant integer value!");
        }
        else block.data.int_val = set_value;
    }

    int CMemIntegerNode::get_value()
    {
        return block.data.int_val;
    }

};
};