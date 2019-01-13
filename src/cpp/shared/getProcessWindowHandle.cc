#include "getProcessWindowHandle.hpp"

HWND g_HWND = NULL;

BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM lParam)
{
  DWORD lpdwProcessId;
  GetWindowThreadProcessId(hwnd, &lpdwProcessId);
  if (lpdwProcessId == lParam)
  {
    g_HWND = hwnd;
    return FALSE;
  }
  return TRUE;
}

HWND GetProcessWindowHandle(int processId)
{
  EnumWindows(EnumWindowsCallback, processId);
  HWND result = g_HWND;
  g_HWND = NULL;

  return result;
}