#include "inexor/flowgraph/node/fl_nodebase.h"
#include <deque>

namespace inexor {
namespace vscript {

    struct CJob
    {
        SDL_Thread* thread;
        CScriptNode* node;
        bool started;
        bool done;
    };

    class CVisualScriptWorker 
    {
        public:

            std::deque<CJob> jobs;

            CVisualScriptWorker();
            ~CVisualScriptWorker();

            void add_job(CScriptNode* job);
            void run_jobs();
    };

};
};
