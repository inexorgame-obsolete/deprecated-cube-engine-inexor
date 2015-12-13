#include "inexor/flowgraph/worker/fl_threadworker.h"


namespace inexor {
namespace vscript {

    CVisualScriptWorker::CVisualScriptWorker()
    {
    }

    CVisualScriptWorker::~CVisualScriptWorker()
    {
    }


    void CVisualScriptWorker::add_job(CScriptNode* node)
    {
        CJob j;
        j.node = node;
        j.started = false;
        j.done = false;
        jobs.push_back(j);
    }


    void CVisualScriptWorker::run_jobs()
    {
        unsigned long start_time = SDL_GetTicks();

        for(unsigned int i=0; i<jobs.size(); i++)
        {
            if(!jobs.at(i).done)
            {
                jobs.at(i).started = true;
                jobs.at(i).node->done_pointer = & jobs.at(i).done;
                jobs.at(i).node->script_execution_start = start_time;
                jobs.at(i).node->in();
            }
        }
    }

};
};
