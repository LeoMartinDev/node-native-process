#include "GetProcessWindowTitleWorker.hpp"

GetProcessWindowTitleWorker::GetProcessWindowTitleWorker(Napi::Function &callback, int processId)
    : AsyncWorker(callback), processId(processId) {}

GetProcessWindowTitleWorker::~GetProcessWindowTitleWorker() {}

void GetProcessWindowTitleWorker::Execute()
{
  this->result = GetProcessWindowTitle(this->processId);
}

void GetProcessWindowTitleWorker::OnOK()
{
  Napi::HandleScope scope(Env());
  Napi::String returnValue = Napi::String::New(Env(), this->result);

  Callback().Call({Env().Null(), returnValue});
}

void GetProcessWindowTitleWorker::OnError(const Napi::Error &e)
{
  Napi::HandleScope scope(Env());

  Callback().Call({e.Value(), Env().Null()});
};