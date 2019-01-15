#include "getProcessWindowHandle.hpp"

HWND g_HWND = NULL;

BOOL IsMainWindow(HWND handle)
{
  return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
  t_HandleData &data = *(t_HandleData *)lParam;
  unsigned long pid = 0;
  
  GetWindowThreadProcessId(handle, &pid);
  if (data.pid != pid || !IsMainWindow(handle))
    return TRUE;
  data.handle = handle;
  return FALSE;
}

HWND GetProcessWindowHandle(int processId)
{
  t_HandleData data;
  data.pid = processId;
  data.handle = 0;
  EnumWindows(EnumWindowsCallback, (LPARAM)&data);
  return data.handle;
}