#include "setProcessToForeground_main.hpp"

bool SetProcessToForeground(int processId)
{
  HWND hWnd = GetProcessWindowHandle(processId);

  if (!IsWindow(hWnd))
  {
    return false;
  }
  BYTE keyState[256] = {0};
  //to unlock SetForegroundWindow we need to imitate Alt pressing
  if (GetKeyboardState((LPBYTE)&keyState))
  {
    if (!(keyState[VK_MENU] & 0x80))
    {
      keybd_event(VK_MENU, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
    }
  }
  WINDOWPLACEMENT place;
  memset(&place, 0, sizeof(WINDOWPLACEMENT));
  place.length = sizeof(WINDOWPLACEMENT);
  GetWindowPlacement(hWnd, &place);

  switch (place.showCmd)
  {
  case SW_SHOWMAXIMIZED:
    ShowWindow(hWnd, SW_SHOWMAXIMIZED);
    break;
  case SW_SHOWMINIMIZED:
    ShowWindow(hWnd, SW_RESTORE);
    break;
  default:
    ShowWindow(hWnd, SW_NORMAL);
    break;
  }
  SetForegroundWindow(hWnd);
  if (GetKeyboardState((LPBYTE)&keyState))
  {
    if (!(keyState[VK_MENU] & 0x80))
    {
      keybd_event(VK_MENU, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    }
  }
  return true;
};

void SetProcessToForegroundCallback(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  int processId;
  Napi::Function callback;
  SetProcessToForegroundWorker *worker;

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
  worker = new SetProcessToForegroundWorker(callback, processId);
  worker->Queue();
}