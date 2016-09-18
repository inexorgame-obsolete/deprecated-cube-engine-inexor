#include "inexor/flowgraph/functions/playsound/fl_playsound.hpp"

namespace inexor {
namespace vscript {

    // TODO: implement playsound correctly
    CFunctionPlaysoundNode::CFunctionPlaysoundNode(const vec position, const char* id)
    {
        pos = position;
        sound_id = atoi(id);
    }

    CFunctionPlaysoundNode::~CFunctionPlaysoundNode()
    {
    }


    void CFunctionPlaysoundNode::in()
    {
        // inexor::sound::playsound(sound_id);
        last_time = SDL_GetTicks();
        out();
    }

    bool CFunctionPlaysoundNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        return false;
    }

    bool CFunctionPlaysoundNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        return false;
    }

};
};
