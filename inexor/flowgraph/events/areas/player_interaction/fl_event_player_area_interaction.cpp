#include "inexor/flowgraph/events/areas/player_interaction/fl_event_player_area_interaction.hpp"
#include "inexor/fpsgame/game.hpp"

namespace inexor {
namespace vscript {
    
    CPlayerAreaInteractionEventNode::CPlayerAreaInteractionEventNode(vec position, INEXOR_VSCRIPT_EVENT_TYPE ev_type)
    {
        type = INEXOR_VSCRIPT_NODE_TYPE_EVENT;
        pos = position;
        event_type = ev_type;
        // player is outside at startup
        // this can change in the next tick if he spawned inside an area!
        area_player_interaction_status = INEXOR_VSCRIPT_PLAYER_AREA_INTERACTION_I_AM_OUTSIDE;
        // this data is invalid at startup
        area_type = INEXOR_VSCRIPT_NODE_TYPE_INVALID;
        area = nullptr;
    }

    CPlayerAreaInteractionEventNode::~CPlayerAreaInteractionEventNode()
    {
    }


    void CPlayerAreaInteractionEventNode::in()
    {
        check_trigger();
    }
    
    void CPlayerAreaInteractionEventNode::check_trigger()
    {
        if(nullptr == area || INEXOR_VSCRIPT_NODE_TYPE_INVALID == area_type) return;
        bool b_IsPlayerInsideArea = false;
        switch(area_type)
        {
            // TODO: support more area types!
            case INEXOR_VSCRIPT_NODE_TYPE_AREA_BOX:
            {
                break;
            }
            case INEXOR_VSCRIPT_NODE_TYPE_AREA_SPHERE:
            {
                b_IsPlayerInsideArea = static_cast<CSphereAreaNode*>(area)->is_point_inside_sphere(game::player1->o);
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
        update_interaction_status(b_IsPlayerInsideArea);
    }

    void CPlayerAreaInteractionEventNode::update_interaction_status(bool is_player_in_sphere)
    {
        if(true == is_player_in_sphere)
        {
            if(INEXOR_VSCRIPT_PLAYER_AREA_INTERACTION_I_AM_OUTSIDE == area_player_interaction_status)
            {
                // player was outside but now is inside
                // change status and trigger (if neccesary)
                area_player_interaction_status = INEXOR_VSCRIPT_PLAYER_AREA_INTERACTION_I_AM_INSIDE;
                //conoutf(CON_DEBUG, "[3DVS-area-player-interaction-event] player1 was outside and now is inside the area!");
                // this is an event which triggers when a players enters an area -> trigger!
                if(INEXOR_VSCRIPT_EVENT_TYPE_PLAYER_ENTER_AREA == event_type) trigger();
            }
        }
        else 
        {
            if(INEXOR_VSCRIPT_PLAYER_AREA_INTERACTION_I_AM_INSIDE == area_player_interaction_status)
            {
                // player was inside but now is outside
                // change status and trigger (if neccesary)
                area_player_interaction_status = INEXOR_VSCRIPT_PLAYER_AREA_INTERACTION_I_AM_OUTSIDE;
                //conoutf(CON_DEBUG, "[3DVS-area-player-interaction-event] player1 was inside and now is outside the area!");
                // this is an event which triggers when a players leaves an area -> trigger!
                if(INEXOR_VSCRIPT_EVENT_TYPE_PLAYER_LEAVE_AREA == event_type) trigger();
            }
        }
    }

    void CPlayerAreaInteractionEventNode::trigger()
    {
        //conoutf(CON_DEBUG, "[3DVS-area-player-interaction-event] I was told to trigger something?");
        out();
    }

};
};
