#include "inexor/flowgraph/timer/fl_timer.hpp"

#include <SDL.h>
#include <thread>

namespace inexor {
namespace vscript {

    CTimerNode::CTimerNode(vec position,  unsigned int interval, unsigned int startdelay, 
                           unsigned int limit, unsigned int cooldown, INEXOR_VSCRIPT_TIME_FORMAT format)
    {
        type = INEXOR_VSCRIPT_NODE_TYPE_TIMER;
        pos = position;

        unsigned int time_format_in_ms = interval;

        // validate the time interval
        clamp(interval, INEXOR_VSCRIPT_MIN_TIMER_INTERVAL, INEXOR_VSCRIPT_MAX_TIMER_INTERVAL);
        timer_interval = time_format_in_ms;
        timer_startdelay = startdelay;
        timer_limit = limit;
        timer_cooldown = cooldown;
        last_time = SDL_GetTicks();
        timer_counter = 0;
        type = INEXOR_VSCRIPT_NODE_TYPE_TIMER;
    }

    CTimerNode::~CTimerNode()
    {
    }


    unsigned int CTimerNode::get_timer_interval()
    {
        return timer_interval;
    }

    void CTimerNode::reset()
    {
        this_time = 0;
        last_time = 0;
    }

    void CTimerNode::in()
    {
        check_if_execution_is_due();
    }

    static int LetsGo(void *ptr)
    {
        // TODO: debug this on any operating system!
        CScriptNode* node = static_cast<CScriptNode*>(ptr);
        conoutf(CON_DEBUG, "[3DVS-threads] thread \f6%s\f7 started!", node->node_name.c_str());
        if(nullptr != node) node->in();
        conoutf(CON_DEBUG, "[3DVS-threads] thread \f6%s\f7 finished!", node->node_name.c_str());
        return 0;
    }

    void CTimerNode::check_if_execution_is_due() 
    {
        if(this_time - last_time >= timer_interval) 
        {
            unsigned int thread_count = 0;
            for(unsigned int i=0; i<children.size(); i++)
            {
                // create a new thread!
                std::thread new_thread(LetsGo, (void *)children[i]);
                // do NOT wait until thread has come to an end!
                new_thread.detach();
                thread_count++;
            }
            last_time = this_time;
            timer_counter++;
        }
    }

    void CTimerNode::render_additional(vec p)
    {
    }
    
    bool CTimerNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        return false;
    }

    bool CTimerNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        return true;
    }

};
};
