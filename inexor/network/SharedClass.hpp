#pragma once
#include "inexor/network/SharedVar.hpp"
#include "inexor/network/SharedOptions.hpp"

/// All classes deriving from this class get detected by our reflection system InexorGlueGen.
class SharedClass
{
public:
    SharedClass() {}
    SharedClass(SharedOption p) {}
};
