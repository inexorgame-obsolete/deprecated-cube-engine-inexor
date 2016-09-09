#include "inexor/flowgraph/events/areas/player_enter_area/fl_event_player_enter_area.hpp"
#include "inexor/fpsgame/game.hpp"

namespace inexor {
namespace vscript {
    
    CPlayerEnterAreaEventNode::CPlayerEnterAreaEventNode(vec position)
    {
        type = INEXOR_VSCRIPT_NODE_TYPE_EVENT_PLAYER_ENTER_AREA;
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
        switch(area_type)
        {
            case INEXOR_VSCRIPT_NODE_TYPE_AREA_BOX:
            {
                break;
            }
            case INEXOR_VSCRIPT_NODE_TYPE_AREA_SPHERE:
            {
                // TODO: change state
                if(static_cast<CSphereAreaNode*>(area)->is_point_inside_sphere(game::player1->o))
                {
                    conoutf(CON_DEBUG, "[3DVS-player-enter-area-event] I'm IN!!!");
                    out();
                }
                else 
                {
                    conoutf(CON_DEBUG, "[3DVS-player-enter-area-event] I'm OUT!!!");
                }
                break;
            }
            case INEXOR_VSCRIPT_NODE_TYPE_AREA_CONE:
            {
                break;
            }
            case INEXOR_VSCRIPT_NODE_TYPE_AREA_CYLINDER:
            {
                break;
            }
        }
    }

    void CPlayerEnterAreaEventNode::out()
    {
    }

};
};
