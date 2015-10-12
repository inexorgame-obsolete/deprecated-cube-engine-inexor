/// @file fl_timer.h (flowgraph's timer implementation)
/// @author Johannes Schneider
/// @brief Timers will be called every [n] miliseconds

// include guard
#ifndef INEXOR_VSCRIPT_MEMBASE_HEADER
#define INEXOR_VSCRIPT_MEMBASE_HEADER

/// project's namespace protection
namespace inexor {
namespace vscript {

/// data type enumeration
enum VSCRIPT_DATA_TYPE 
{
    TYPE_INTEGER_VALUE,  /// always signed
    TYPE_FLOATING_POINT, /// always double
    TYPE_STRING,
    TYPE_BOOLEAN,
    TYPE_VECTOR,
    TYPE_TIMESTAMP,
    TYPE_COLOR,
    // TODO...
};


/// TODO: Memory...
class CMemory
{
    CMemory();
    ~CMemory();

    void in();
    void run();
    void out();
};


/// end of namespace
};
};

#endif
