#include "debug.h"

namespace slam_debug
{
    void breakpoint()
    {
#ifndef _RELEASE
        __debugbreak();
#endif
    }

}