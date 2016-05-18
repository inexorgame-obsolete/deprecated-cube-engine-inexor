#include "inexor/flowgraph/timer/fl_timer.hpp"

#include <SDL.h>
#include <SDL_thread.h>

namespace inexor {
namespace vscript {

    CTimerNode::CTimerNode(vec position, 
                           unsigned int interval, 
                           unsigned int startdelay, 
                           unsigned int limit, 
                           unsigned int cooldown, 
                           const char* name, 
                           const char* comment, 
                           INEXOR_VSCRIPT_TIME_FORMAT format)
    {
        pos = position;
        node_name = name;
        node_comment = comment;
        
        // TODO: convert the time format
        unsigned int time_format_in_ms = interval;

        // validate the time interval
        clamp(interval, INEXOR_VSCRIPT_MIN_TIMER_INTERVAL, INEXOR_VSCRIPT_MAX_TIMER_INTERVAL);
        timer_interval = time_format_in_ms;
        timer_startdelay = startdelay;
        timer_limit = limit;
        timer_cooldown = cooldown;
        last_time = SDL_GetTicks();
        timer_counter = 0;
        type = NODE_TYPE_TIMER;
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
        CScriptNode* node = static_cast<CScriptNode* >(ptr);
        if(nullptr != node) node->in();
        return 0;
    }

    void CTimerNode::check_if_execution_is_due() 
    {
        // checks if timer interval has exceeded
        if(this_time - last_time >= timer_interval) 
        {
            #ifdef INEXOR_VSCRIPT_TIMER_DEBUGGING
                conoutf(CON_DEBUG, "%s: Its time to see if I should run some code", node_name.c_str() );
            #endif 

            for(unsigned int i=0; i<children.size(); i++)
            {
                #ifdef INEXOR_VSCRIPT_TIMER_DEBUGGING
                    conoutf(CON_DEBUG, "%s: thread started!", node_name.c_str() );
                #endif

                // start a new thread
                SDL_Thread* thread = SDL_CreateThread(LetsGo, "LetsGo", (void *)children[i]);
                threads.push_back(thread);
            }
            last_time = this_time;
            timer_counter++;
        }
    }

    // render additional timer data
    void CTimerNode::render_additional(vec p)
    {
        particle_text(p + vec(0.0f, 0.0f, -(2.0f+boxsize) ), "attributes here! :)", PART_TEXT, 1, 0xFFFFFF, 1.0f);
    }


    // Timers can be parent nodes but NOT child nodes!
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
