#ifndef SET_PROCESS_TO_FOREGROUND_HPP
#define SET_PROCESS_TO_FOREGROUND_HPP

#include <napi.h>
#include <Windows.h>
#include "../shared/getProcessWindowHandle.hpp"
#include "SetProcessToForegroundWorker.hpp"

bool SetProcessToForeground(int processId);
void SetProcessToForegroundCallback(const Napi::CallbackInfo &info);

#endif