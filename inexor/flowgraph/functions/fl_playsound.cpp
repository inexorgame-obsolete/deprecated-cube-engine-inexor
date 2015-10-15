#include "inexor/flowgraph/functions/fl_playsound.h"
#include "inexor/fpsgame/game.h"

namespace inexor {
namespace vscript {

    function_playsound_node::function_playsound_node(vec pos, int sound_id)
    {
    }

    function_playsound_node::~function_playsound_node()
    {
    }

    void function_playsound_node::in()
    {
    }

    void function_playsound_node::run()
    {
        /// TODO: playsound
        playsound(S_V_BASECAP);
    }
    
    void function_playsound_node::out()
    {
        for(unsigned int i = 0; i < outgoing.size(); i++) outgoing[i]->in();
    }
    
    void function_playsound_node::reset()
    {
    }

/// end of namespace
};
};
