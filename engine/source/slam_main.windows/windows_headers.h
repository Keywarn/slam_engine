#pragma once

// Some of the windows header files need to be included in a very specific
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