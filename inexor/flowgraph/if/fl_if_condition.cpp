#include "inexor/flowgraph/if/fl_if_condition.hpp"

namespace inexor {
namespace vscript {

    CIfNode::CIfNode(const vec position)
    {
        type = INEXOR_VSCRIPT_NODE_TYPE_IF;
        pos = position;
        statement = nullptr;
        condition_true_node = nullptr;
        condition_false_node = nullptr;
    }

    CIfNode::~CIfNode()
    {
    }


    void CIfNode::in()
    {
        check_condition();
    }

    void CIfNode::check_condition()
    {
        // TODO: decide about node box coloring.
        if(nullptr != statement)
        {
            default_box_color = INEXOR_VSCRIPT_COLOR_OPERATOR;
            if (true == statement->get_value()) condition_true_out();
            else condition_false_out();
        }
        else
        {
            default_box_color = INEXOR_VSCRIPT_COLOR_PENDING;
        }
    }

    void CIfNode::condition_true_out()
    {
        spdlog::get("global")->debug() << "[3DVS-if-condition] boolean statement '%s' turned out to be TRUE.", statement->node_name.c_str();
        if(nullptr != condition_true_node) condition_true_node->in();
        else
        {
            spdlog::get("global")->debug() << "[3DVS-if-condition] no outgoing node for TRUE conditions found! Script ends.";
        }
    }

    void CIfNode::condition_false_out()
    {
        spdlog::get("global")->debug() << "[3DVS-if-condition] boolean statement '%s' turned out to be FALSE.", statement->node_name.c_str();
        if(nullptr != condition_false_node) condition_false_node->in();
        else
        {
            spdlog::get("global")->debug() << "[3DVS-if-condition] no outgoing node for FALSE conditions found! Script ends.";
        }
    }

    void CIfNode::render_additional(vec p)
    {
        particle_text(p + vec(0.0f, 0.0f, -(2.0f+boxsize) ), "I don't know what to say", PART_TEXT, 1, 0xFFFFFF, 1.0f);
    }

    bool CIfNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        switch (parent->type)
        {
            case INEXOR_VSCRIPT_NODE_TYPE_MEMORY_BOOL:
            {
                if(nullptr != parent)
                {
                    // TODO: debug!
                    // copy boolean statement node's pointer
                    statement = static_cast<CMemBoolNode*>(parent);
                    // TODO: this requires disconnect_nodes to be implemented!
                    // TODO: remove relation from old node!
                    spdlog::get("global")->debug() << "[3DVS-if-condition] linked '%s' as boolean statement.", parent->node_name.c_str();
                    return true;
                }
                default_box_color = INEXOR_VSCRIPT_COLOR_PENDING;
                spdlog::get("global")->debug() << "[3DVS-if-condition] invalid boolean statement node pointer!";
                return false;
                break;
            }
            case INEXOR_VSCRIPT_NODE_TYPE_TIMER:
            {
                // TODO: implement more specific rules!
                return true;
                break;
            }
        }
        return false;
    }

    bool CIfNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        return true;
    }


};
};
