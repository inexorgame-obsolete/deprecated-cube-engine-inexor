#include "inexor/flowgraph/functions/fl_playsound.h"
#include "inexor/fpsgame/game.h"

namespace inexor {
namespace vscript {

    /// TODO: implement playsound correctly

    CFunctionPlaysoundNode::CFunctionPlaysoundNode(vec position, const char* id)
    {
        pos = position;
        sound_id = atoi(id);
    }


    CFunctionPlaysoundNode::~CFunctionPlaysoundNode()
    {
    }


    void CFunctionPlaysoundNode::run()
    {
        playsound(sound_id);
        last_time = SDL_GetTicks();
        out();
    }
    
    void CFunctionPlaysoundNode::reset()
    {
    }
    
};
};
