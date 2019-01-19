#include "getForegroundWindowPid_main.hpp"

int GetForegroundWindowPid() {
    DWORD pid;
    HWND hwnd = GetForegroundWindow();
    
    GetWindowThreadProcessId(hwnd, &pid);
    return static_cast<int>(pid);
}

void GetForegroundWindowPidCallback(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Function callback;
    GetForegroundWindowPidWorker* worker;

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Invalid number of argument!").ThrowAsJavaScriptException();
        return;
    }
    if (!info[0].IsFunction()) {
        Napi::TypeError::New(env, "Argument 'callback' must be of type 'Function'!").ThrowAsJavaScriptException();
        return;
    }
    callback = info[0].As<Napi::Function>();
    worker = new GetForegroundWindowPidWorker(callback); 
    worker->Queue();
}