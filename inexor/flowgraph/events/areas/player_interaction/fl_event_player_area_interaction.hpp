/// @file fl_event_player_enter_area.hpp
/// @author Johannes Schneider
/// @brief Implements events which will be triggered by player interactions with areas.

#ifndef INEXOR_VSCRIPT_AREA_EVENT_PLAYER_INTERACTION_HEADER
#define INEXOR_VSCRIPT_AREA_EVENT_PLAYER_INTERACTION_HEADER

#include "inexor/flowgraph/events/areas/base/fl_area_event_base.hpp"
#include "inexor/fpsgame/game.hpp"

namespace inexor {
namespace vscript {

    /// @brief A player can be either inside or outside an area
    enum INEXOR_VSCRIPT_PLAYER_AREA_INTERACTION_STATUS
    {
        INEXOR_VSCRIPT_PLAYER_AREA_INTERACTION_I_AM_OUTSIDE = 0,
        INEXOR_VSCRIPT_PLAYER_AREA_INTERACTION_I_AM_INSIDE,
    };

    class CPlayerAreaInteractionEventNode : public CAreaEventNode
    {
        public:

            CPlayerAreaInteractionEventNode(const vec, const INEXOR_VSCRIPT_EVENT_TYPE);
            ~CPlayerAreaInteractionEventNode();
    
            void in();
            void check_trigger();
            void update_interaction_status(const bool);
            void trigger();
            
        protected:

            INEXOR_VSCRIPT_PLAYER_AREA_INTERACTION_STATUS area_player_interaction_status;

    };

};
};

#endif
