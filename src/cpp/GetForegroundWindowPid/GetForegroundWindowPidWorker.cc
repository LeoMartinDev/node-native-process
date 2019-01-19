#include "GetForegroundWindowPidWorker.hpp"

GetForegroundWindowPidWorker::GetForegroundWindowPidWorker(Napi::Function &callback)
    : AsyncWorker(callback) {}

GetForegroundWindowPidWorker::~GetForegroundWindowPidWorker() {}

void GetForegroundWindowPidWorker::Execute()
{
  this->result = GetForegroundWindowPid();
}

void GetForegroundWindowPidWorker::OnOK()
{
  Napi::HandleScope scope(Env());

  Callback().Call({Env().Null(), Napi::Number::New(Env(), this->result)});
}

void GetForegroundWindowPidWorker::OnError(const Napi::Error &e)
{
  Napi::HandleScope scope(Env());

  Callback().Call({e.Value(), Env().Null()});
};