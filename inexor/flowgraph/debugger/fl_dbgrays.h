/// @file fl_dbgrays.h
/// @author Johannes Schneider
/// @brief Debug rays help to understand the position and view vector of new placed nodes.

#ifndef INEXOR_VSCRIPT_DEBUGRAY_HEADER
#define INEXOR_VSCRIPT_DEBUGRAY_HEADER

#include "inexor/engine/engine.h"


namespace inexor {
namespace vscript {

    class CDebugRay
    {
        public:
        vec pos;
        vec target;
    };

};
};

#endif
