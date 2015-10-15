#include "inexor/flowgraph/functions/fl_playsound.h"
#include "inexor/fpsgame/game.h"

namespace inexor {
namespace vscript {

    function_playsound_node::function_playsound_node(vec pos, const char* id)
    {
        position = pos;
        sound_id = atoi(id);
        //int sound_id;
        //int flags;
        //int loops;
        //int fade;
        //int chanid;
        //int radius;
        //int expire;
        //vec location;
        //extentity *ent;
    }

    function_playsound_node::~function_playsound_node()
    {
    }


    void function_playsound_node::in()
    {
        run();
    }

    void function_playsound_node::run()
    {
        /// TODO: Implement playsound correctly!
        playsound(sound_id);
    }
    
    void function_playsound_node::out()
    {
        for(unsigned int i = 0; i < outgoing.size(); i++) outgoing[i]->in();
    }
    
    void function_playsound_node::reset()
    {
    }

/// end of namespace
};
};
