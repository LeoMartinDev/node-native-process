#include "getProcessesByName_main.hpp"

std::vector<int> GetProcessesByName(const std::string &processName)
{
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    std::vector<int> pids;

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (stricmp(entry.szExeFile, processName.c_str()) == 0)
            {  
                pids.push_back(entry.th32ProcessID);
            }
        }
    }

  CloseHandle(snapshot);
  return pids;
}

void GetProcessesByNameCallback(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string processName;
    Napi::Function callback;
    GetProcessesByNameWorker* worker;

    if (info.Length() < 2) {
        Napi::TypeError::New(env, "Invalid number of argument!").ThrowAsJavaScriptException();
        return;
    }
    if (info.Length() < 1 || !info[0].IsString())
    {
        Napi::TypeError::New(env, "Argument 'processName' must be of type 'String'!").ThrowAsJavaScriptException();
        return;
    }
    if (!info[1].IsFunction()) {
        Napi::TypeError::New(env, "Argument 'callback' must be of type 'Function'!").ThrowAsJavaScriptException();
        return;
    }
    processName = info[0].As<Napi::String>();
    callback = info[1].As<Napi::Function>();
    worker = new GetProcessesByNameWorker(callback, processName); 
    worker->Queue();
}