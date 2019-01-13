#ifndef GET_PROCESS_WINDOW_TITLE_CC
#define GET_PROCESS_WINDOW_TITLE_CC

#include <napi.h>
#include <cstdio>
#include <iostream>
#include <vector>
#include "getProcessWindowTitle_main.hpp"

class GetProcessWindowTitleWorker : public Napi::AsyncWorker
{
public:
  GetProcessWindowTitleWorker(Napi::Function &callback, int processId);

  ~GetProcessWindowTitleWorker();

protected:
  void Execute();
  void OnOK();
  void OnError(const Napi::Error &e);

private:
  int processId;
  std::string result;
};

#endif