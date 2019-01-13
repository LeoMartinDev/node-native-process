#ifndef GET_PROCESSES_BY_NAME_WORKER_HPP
#define GET_PROCESSES_BY_NAME_WORKER_HPP

#include <napi.h>
#include <cstdio>
#include <iostream>
#include <vector>
#include "getProcessesByName_main.hpp"

class GetProcessesByNameWorker : public Napi::AsyncWorker
{
public:
  GetProcessesByNameWorker(Napi::Function &callback, const std::string &processName);

  ~GetProcessesByNameWorker();

protected:
  void Execute();
  void OnOK();
  void OnError(const Napi::Error &e);

private:
  std::string processName;
  std::vector<int> result;
};

#endif