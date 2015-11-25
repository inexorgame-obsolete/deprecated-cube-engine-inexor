#include "inexor/flowgraph/sleep/fl_sleep.h"

namespace inexor {
namespace vscript {

    CSleepNode::CSleepNode(vec pos, 
                           unsigned int sleeptime, 
                           const char* name, 
                           const char* comment)
    {
        sleep_interval = sleeptime;
    }


    CSleepNode::~CSleepNode()
    {
    }


    void CSleepNode::run()
    {
        /// save the current time
        sleep_start = SDL_GetTicks();
        sleep_end = sleep_start + sleep_interval;
        /// call outgoing method once waiting has finished
        /// TODO: multithreading?
        if(SDL_GetTicks() >= sleep_end)
        {
            out();
        }
    }


/// end of namespaces
};
};
