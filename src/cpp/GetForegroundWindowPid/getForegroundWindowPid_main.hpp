#ifndef GET_FOREGROUND_WINDOW_PID_MAIN_HPP
#define GET_FOREGROUND_WINDOW_PID_MAIN_HPP

#include <napi.h>
#include <Windows.h>
#include "GetForegroundWindowPidWorker.hpp"

int GetForegroundWindowPid();
void GetForegroundWindowPidCallback(const Napi::CallbackInfo& info);

#endif