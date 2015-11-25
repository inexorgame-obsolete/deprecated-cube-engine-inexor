#include "inexor/flowgraph/functions/fl_playsound.h"
#include "inexor/fpsgame/game.h"

namespace inexor {
namespace vscript {

    CFunctionPlaysoundNode::CFunctionPlaysoundNode(vec pos, const char* id)
    {
        position = pos;
        sound_id = atoi(id);
        //int sound_id;
        //int flags;
        //int loops;
        //int fade;
        //int chanid;
        //int radius;
        //int expire;
        //vec location;
        //extentity *ent;
    }


    CFunctionPlaysoundNode::~CFunctionPlaysoundNode()
    {
    }


    void CFunctionPlaysoundNode::run()
    {
        /// TODO: Implement playsound correctly!
        playsound(sound_id);
    }
    

/// end of namespaces
};
};
