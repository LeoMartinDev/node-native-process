#include <napi.h>
#include <chrono>
#include <thread>
#include <cstdio>
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <vector>

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

    if (info.Length() < 3) {
        Napi::TypeError::New(env, "Invalid argument count").ThrowAsJavaScriptException();
        return;
    }
    if (info.Length() < 1 || !info[0].IsString())
    {
        Napi::TypeError::New(env, "Argument 'processName' is not a string!").ThrowAsJavaScriptException();
        return;
    }
    if (!info[1].IsFunction()) {
        Napi::TypeError::New(env, "Argument 'callback' is not a function!").ThrowAsJavaScriptException();
        return;
    }
    Napi::Function cb = info[1].As<Napi::Function>();
    std::string processName = info[0].As<Napi::String>().Value();

    (new GetProcessesByNameWorker(cb, processName))->Queue();
}

class GetProcessesByNameWorker : public Napi::AsyncWorker {
    public:
        GetProcessesByNameWorker(Napi::Function& callback, std::string& processName)
        : AsyncWorker(callback), processName(processName) {}

        ~GetProcessesByNameWorker() {}
    void Execute() {
        std::vector<int> pids = GetProcessesByName(this->processName);

        this->returnValue = Napi::Array::New(Env());
        for (int i = 0; i < pids.size(); i++) {
            this->returnValue[i] = Napi::Number::New(Env(), pids.at(i));
        }
    }

    void OnOK() {
        Callback().Call({Env().Null(), returnValue});
    }

    void OnError(const Napi::Error& e) {
        Callback().Call({e.Value(), Env().Null()});
    }

    private:
        std::string processName;
        Napi::Array returnValue;
};