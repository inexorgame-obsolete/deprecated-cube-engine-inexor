#include "inexor/flowgraph/sleep/fl_sleep.h"

namespace inexor {
namespace vscript {

    CSleepNode::CSleepNode(vec pos, 
                           unsigned int sleeptime, 
                           const char* name, 
                           const char* comment)
    {
        sleep_interval = sleeptime;
        position = pos;

    }


    CSleepNode::~CSleepNode()
    {
    }


    void CSleepNode::run()
    {
        /// TODO: Implement multithreading?
        if(!sleep_active)
        {
            sleep_start = SDL_GetTicks();
            sleep_active = true;
            sleep_end = sleep_start + sleep_interval;
        }
        if(SDL_GetTicks() >= sleep_end)
        {
            CScriptNode::out();
            sleep_active = false;
        }
    }

    
    void CSleepNode::reset()
    {
    }


/// end of namespaces
};
};
