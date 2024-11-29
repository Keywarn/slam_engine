#include <slam_main/debug/debug.h>
#include "windows_headers.h"

#include <tchar.h>
#include <exception>
#include <debugapi.h>

namespace slam_debug
{
    void terminate()
    {
#ifndef _RELEASE
        std::terminate();
#endif
    }

    void log(const char* output, bool newline)
    {
#ifndef _RELEASE
        OutputDebugString(_T(output));
        if (newline)
        {
            OutputDebugString(_T("\n"));
        }
#endif
    }

}