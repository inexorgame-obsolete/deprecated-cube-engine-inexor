#pragma once

namespace recorder
{
    extern void stop();
    extern void capture(bool overlay = true);
    extern void cleanup();
}
