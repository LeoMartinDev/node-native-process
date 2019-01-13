#ifndef SET_PROCESS_TO_FOREGROUND_WORKER_HPP
#define SET_PROCESS_TO_FOREGROUND_WORKER_HPP

#include <napi.h>
#include <cstdio>
#include <iostream>
#include "setProcessToForeground_main.hpp"

class SetProcessToForegroundWorker : public Napi::AsyncWorker
{
public:
  SetProcessToForegroundWorker(Napi::Function &callback, int processId);

  ~SetProcessToForegroundWorker();

protected:
  void Execute();
  void OnOK();
  void OnError(const Napi::Error &e);

private:
  int processId;
  bool result;
};

#endif