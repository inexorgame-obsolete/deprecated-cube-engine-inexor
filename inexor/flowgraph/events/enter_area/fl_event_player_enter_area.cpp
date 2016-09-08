#include "inexor/flowgraph/events/enter_area/fl_event_player_enter_area.hpp"

namespace inexor {
namespace vscript {

    CPlayerEnterAreaEventNode::CPlayerEnterAreaEventNode(vec position)
    {
        // TODO: specify event conditions? invent new event types?
        type = INEXOR_VSCRIPT_NODE_TYPE_EVENT;
        pos = position;
        event_type = INEXOR_VSCRIPT_PLAYER_ENTER_AREA;
        area_type = INEXOR_VSCRIPT_NODE_TYPE_INVALID;
        area = nullptr;
    }

    CPlayerEnterAreaEventNode::~CPlayerEnterAreaEventNode()
    {
    }


    void CPlayerEnterAreaEventNode::in()
    {
        check_trigger();
    }
    
    void CPlayerEnterAreaEventNode::check_trigger()
    {
        conoutf(CON_DEBUG, "[3DVS-player-enter-area-event] checking... aha!");
    }

    void CPlayerEnterAreaEventNode::out()
    {
        // TODO: do we even need this?
    }

    // only allow areas to be linked
    bool CPlayerEnterAreaEventNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        switch (parent->type)
        {
            case INEXOR_VSCRIPT_NODE_TYPE_AREA_BOX:
            case INEXOR_VSCRIPT_NODE_TYPE_AREA_CONE:
            case INEXOR_VSCRIPT_NODE_TYPE_AREA_SPHERE:
            case INEXOR_VSCRIPT_NODE_TYPE_AREA_CYLINDER:
            {
                area = parent;
                area_type = parent->type;
                conoutf(CON_DEBUG, "[3DVS-player-enter-area-event] linked '%s' as event trigger area.", parent->node_name.c_str());
                return true;
                break;
            }
        }
        return false;
    }

    bool CPlayerEnterAreaEventNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        return false;
    }

};
};
