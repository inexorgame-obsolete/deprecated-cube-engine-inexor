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
        block.data.int_val = 0;
    }

    CMemIntegerNode::~CMemIntegerNode()
    {
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
    }

    int CMemIntegerNode::get_value()
    {
        return block.data.int_val;
    }

};
};