#include "inexor/flowgraph/functions/playsound/fl_playsound.hpp"

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

    bool CFunctionPlaysoundNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        return false;
    }

    // a function itself can not start any code at all!
    bool CFunctionPlaysoundNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        return false;
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
