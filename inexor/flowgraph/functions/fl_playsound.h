/// @file fl_playsound.h
/// @author Johannes Schneider
/// @brief This game engine function plays a sound by its sound id
/// 
/// TODO: We need a good interface for function parameters here (CEF!)
/// 
/// .-------------------------------------------------------------------------------------------------.
/// | playsound([sound_id]);                                                                          |
/// |_________________________________________________________________________________________________|
/// |                                                                                                 |
/// | Plays a game sound by its id.                                                                   |
/// |                                                                                                 |
/// ._________________________________________________________________________________________________.
/// 


#ifndef INEXOR_VSCRIPT_PLAYSOUND_HEADER
#define INEXOR_VSCRIPT_PLAYSOUND_HEADER

/// conoutf implementation
#include "inexor/engine/engine.h"

/// Include base class
#include "inexor/flowgraph/node/fl_nodebase.h"
#include "inexor/flowgraph/functions/fl_functionbase.h"

/// Inexor 
namespace inexor {
namespace vscript {

    class CFunctionPlaysoundNode : public CScriptNode
    {
        protected:

            //int playsound(int n, const vec *loc, extentity *ent, int flags, int loops, int fade, int chanid, int radius, int expire)
            int sound_id;
            int flags;
            int loops;
            int fade;
            int chanid;
            int radius;
            int expire;

            vec location;
            extentity *ent;

        public:

            /// Lets start with a simple version here
            CFunctionPlaysoundNode(vec, const char*);
            ~CFunctionPlaysoundNode();

            /// TODO: implement more methods!
            void run();
            void reset();
    };

/// end of namespace
};
};

#endif