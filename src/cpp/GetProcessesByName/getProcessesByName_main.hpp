#ifndef GET_PROCESSES_BY_NAME_MAIN_HPP
#define GET_PROCESSES_BY_NAME_MAIN_HPP

#include <napi.h>
#include <chrono>
#include <thread>
#include <cstdio>
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <vector>
#include "GetProcessesByNameWorker.hpp"

std::vector<int> GetProcessesByName(const std::string &processName);
void GetProcessesByNameCallback(const Napi::CallbackInfo& info);

#endif