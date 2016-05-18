/// @file fl_playsound.h
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

            CFunctionPlaysoundNode(vec, const char*);
            ~CFunctionPlaysoundNode();

            void in();
            void run();
            void out();
            void reset();


            bool OnLinkAsChildNodeAttempt(CScriptNode* parent)
            {
                return false;
            }
            bool OnLinkAsParentNodeAttempt(CScriptNode* child)
            {
                return false;
            }
    };

};
};

#endif
