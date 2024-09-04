#pragma once
#include <main.h>

// Some of the windows header files need to be included in a very specific
// order - this should probably go in a separate file/pch...

#define NOMINMAX

#include <winsock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <ShlObj.h>
#include <shlwapi.h>
#include <winternl.h>
#include <mswsock.h>
#include <processthreadsapi.h>
#include <DbgEng.h>
#include <DbgHelp.h>
#include <wrl/client.h>

#ifndef _WINDOWS
int main(int argc, char* argv[])
{
    return cx::entry_point(argc, argv);
}
#else
//{
//    return entry_point(__argc, __argv);
//}

int main()
{
    return entry_point(__argc, __argv);
}
#endif