#ifndef GET_FOREGROUND_WINDOW_PID_WORKER_HPP
#define GET_FOREGROUND_WINDOW_PID_WORKER_HPP

#include <napi.h>
#include <cstdio>
#include <iostream>
#include <vector>
#include "getForegroundWindowPid_main.hpp"

class GetForegroundWindowPidWorker : public Napi::AsyncWorker
{
public:
  GetForegroundWindowPidWorker(Napi::Function &callback);

  ~GetForegroundWindowPidWorker();

protected:
  void Execute();
  void OnOK();
  void OnError(const Napi::Error &e);

private:
  int result;
};

#endif