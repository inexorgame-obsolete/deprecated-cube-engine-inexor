#include "inexor/flowgraph/functions/fl_playsound.hpp"

namespace inexor {
namespace vscript {

    // TODO: implement playsound correctly

    CFunctionPlaysoundNode::CFunctionPlaysoundNode(vec position, const char* id)
    {
        pos = position;
        sound_id = atoi(id);
    }


    CFunctionPlaysoundNode::~CFunctionPlaysoundNode()
    {
    }


    void CFunctionPlaysoundNode::in()
    {
        playsound(sound_id);
        last_time = SDL_GetTicks();
        out();
    }


    void CFunctionPlaysoundNode::reset()
    {
    }

    void CFunctionPlaysoundNode::out()
    {
    }

    void CFunctionPlaysoundNode::run()
    {
    }

};
};
