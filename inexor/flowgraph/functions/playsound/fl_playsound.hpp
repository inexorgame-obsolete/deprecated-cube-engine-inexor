/// @file fl_playsound.hpp
/// @author Johannes Schneider
/// @brief

#ifndef INEXOR_VSCRIPT_PLAYSOUND_HEADER
#define INEXOR_VSCRIPT_PLAYSOUND_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"

namespace inexor {
namespace vscript {

    class CFunctionPlaysoundNode : public CScriptNode
    {
        protected:

            int sound_id;
            /*
            int flags;
            int loops;
            int fade;
            int chanid;
            int radius;
            int expire;
            vec location;
            extentity *ent;
            */

        public:

            CFunctionPlaysoundNode(vec, const char*);
            ~CFunctionPlaysoundNode();

            void in();

            bool OnLinkAsChildNodeAttempt(CScriptNode*);
            bool OnLinkAsParentNodeAttempt(CScriptNode*);
    };

};
};

#endif
