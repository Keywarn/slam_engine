#pragma once

namespace slam_debug
{
    void breakpoint();
    void terminate();

    void log(char const* output, bool newline = true);
}