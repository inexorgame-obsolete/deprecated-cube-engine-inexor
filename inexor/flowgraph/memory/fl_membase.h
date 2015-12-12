// @file fl_timer.h (flowgraph's timer implementation)
// @author Johannes Schneider
// @brief Timers will be called every [n] miliseconds

#ifndef INEXOR_VSCRIPT_MEMBASE_HEADER
#define INEXOR_VSCRIPT_MEMBASE_HEADER

namespace inexor {
namespace vscript {

    enum VSCRIPT_DATA_TYPE 
    {
        TYPE_INTEGER_VALUE,  // always signed
        TYPE_FLOATING_POINT, // always double
        TYPE_STRING,
        TYPE_BOOLEAN,
        TYPE_VECTOR,
        TYPE_TIMESTAMP,
        TYPE_COLOR,
    };


    // TODO: use std::any
    class CMemoryNode
    {
        CMemoryNode();
        ~CMemoryNode();

        void in();
        void run();
        void out();
    };

};
};

#endif
