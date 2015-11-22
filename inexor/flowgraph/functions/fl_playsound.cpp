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


    void CFunctionPlaysoundNode::in()
    {
        run();
    }

    void CFunctionPlaysoundNode::run()
    {
        /// TODO: Implement playsound correctly!
        playsound(sound_id);
    }
    
    void CFunctionPlaysoundNode::out()
    {
        for(unsigned int i = 0; i < outgoing.size(); i++) outgoing[i]->in();
    }
    
    void CFunctionPlaysoundNode::reset()
    {
    }

/// end of namespaces
};
};
