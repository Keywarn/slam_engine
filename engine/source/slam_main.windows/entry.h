#pragma once
#include "windows_headers.h"

#ifndef _WINDOWS
int main(int argc, char* argv[]);
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
#endif