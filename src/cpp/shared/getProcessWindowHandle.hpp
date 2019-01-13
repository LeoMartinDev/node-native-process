#ifndef GET_PROCESS_WINDOW_HANDLE_HPP
#define GET_PROCESS_WINDOW_HANDLE_HPP

#include <napi.h>
#include <Windows.h>
#include <cstdio>
#include <iostream>
#include <vector>
#include <AtlBase.h>
#include <AtlConv.h>

BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM lParam);
HWND GetProcessWindowHandle(int processId);

#endif