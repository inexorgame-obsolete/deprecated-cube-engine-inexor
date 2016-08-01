#include "inexor/flowgraph/memory/fl_membase.hpp"

namespace inexor {
namespace vscript {

    CMemoryNode::CMemoryNode(vec position,
                             VSCRIPT_DATA_TYPE type,
                             const char* value,
                             const char* name = "new data",
                             const char* comment = "comment")
    {
        pos = position;
        node_name = name;
        node_comment = comment;

        default_box_color = VSCRIPT_COLOR_MEMORY;
        block.type = type;

        // set memory
        switch (type)
        {
            case VS_DATA_TYPE_INTEGER:
            {
                block.data.int_val = atoi(value);
                break;
            }
            case VS_DATA_TYPE_FLOATING_POINT:
            {
                break;
            }
            case VS_DATA_TYPE_STRING:
            {
                break;
            }
            case VS_DATA_TYPE_BOOLEAN:
            {
                break;
            }
            default:
            {
                break;
            }
        }
    }

    CMemoryNode::~CMemoryNode()
    {
    }

};
};
