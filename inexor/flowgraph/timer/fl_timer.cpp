#include "inexor/flowgraph/timer/fl_timer.hpp"

#include <SDL.h>
#include <thread>

namespace inexor {
namespace vscript {

    CTimerNode::CTimerNode(vec position,  unsigned int interval, unsigned int startdelay, 
                           unsigned int limit, unsigned int cooldown, const char* name, 
                           const char* comment, INEXOR_VSCRIPT_TIME_FORMAT format)
    {
        type = INEXOR_VSCRIPT_NODE_TYPE_TIMER;
        pos = position;
        node_name = name;
        node_comment = comment;
        
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
        // checks if timer interval has exceeded
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

            //conoutf(CON_DEBUG, "[3DVS-threads] timer \f0%s\f7: started %d threads.", node_name.c_str(), thread_count);
            last_time = this_time;
            timer_counter++;
        }
    }

    // render additional timer data
    void CTimerNode::render_additional(vec p)
    {
        // TODO: 1 ms display time??
        particle_text(p + vec(0.0f, 0.0f, -(2.0f+boxsize) ), "attributes here! :)", PART_TEXT, 1, 0xFFFFFF, 1.0f);
    }
    
    // timers can be parent nodes but NOT child nodes!
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
