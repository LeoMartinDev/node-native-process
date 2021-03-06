#include "getProcessWindowTitle_main.hpp"

std::string GetProcessWindowTitle(int processId)
{
  HWND windowHandle = GetProcessWindowHandle(processId);
  const DWORD TITLE_SIZE = 1024;
  WCHAR windowTitle[TITLE_SIZE];

  if (GetWindowTextW(windowHandle, windowTitle, TITLE_SIZE) == 0)
  {
    throw std::exception("GetProcessWindowTitle failed!");
  }
  return std::string(CW2A(windowTitle));
}

void GetProcessWindowTitleCallback(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  int processId;
  Napi::Function callback;
  GetProcessWindowTitleWorker *worker;

  if (info.Length() < 2)
  {
    Napi::TypeError::New(env, "Invalid number of argument!").ThrowAsJavaScriptException();
    return;
  }
  if (info.Length() < 1 || !info[0].IsNumber())
  {
    Napi::TypeError::New(env, "Argument 'processId' must be of type 'Number'!").ThrowAsJavaScriptException();
    return;
  }
  if (!info[1].IsFunction())
  {
    Napi::TypeError::New(env, "Argument 'callback' must be of type 'Function'!").ThrowAsJavaScriptException();
    return;
  }
  processId = info[0].As<Napi::Number>();
  callback = info[1].As<Napi::Function>();
  worker = new GetProcessWindowTitleWorker(callback, processId);
  worker->Queue();
}