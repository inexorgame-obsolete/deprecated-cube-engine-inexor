#include "inexor/flowgraph/functions/fl_playsound.h"
#include "inexor/fpsgame/game.h"

namespace inexor {
namespace vscript {

    /// TODO: implement playsound correctly

    CFunctionPlaysoundNode::CFunctionPlaysoundNode(vec pos, const char* id)
    {
        position = pos;
        sound_id = atoi(id);
    }


    CFunctionPlaysoundNode::~CFunctionPlaysoundNode()
    {
    }


    void CFunctionPlaysoundNode::run()
    {
        playsound(sound_id);
        *done_pointer = true;
    }
    
    void CFunctionPlaysoundNode::reset()
    {
    }
    
};
};
