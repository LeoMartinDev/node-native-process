#ifndef GET_PROCESS_WINDOW_TITLE_HPP
#define GET_PROCESS_WINDOW_TITLE_HPP

#include <napi.h>
#include "../shared/getProcessWindowHandle.hpp"
#include "GetProcessWindowTitleWorker.hpp"

std::string GetProcessWindowTitle(int processId);
void GetProcessWindowTitleCallback(const Napi::CallbackInfo &info);

#endif