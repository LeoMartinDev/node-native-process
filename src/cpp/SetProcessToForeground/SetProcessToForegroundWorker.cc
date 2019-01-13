#include "SetProcessToForegroundWorker.hpp"

SetProcessToForegroundWorker::SetProcessToForegroundWorker(Napi::Function &callback, int processId)
    : AsyncWorker(callback), processId(processId) {}

SetProcessToForegroundWorker::~SetProcessToForegroundWorker() {}

void SetProcessToForegroundWorker::Execute()
{
  this->result = SetProcessToForeground(this->processId);
}

void SetProcessToForegroundWorker::OnOK()
{
  Napi::HandleScope scope(Env());
  Napi::Boolean returnValue = Napi::Boolean::New(Env(), this->result);

  Callback().Call({Env().Null(), returnValue});
}

void SetProcessToForegroundWorker::OnError(const Napi::Error &e)
{
  Napi::HandleScope scope(Env());

  Callback().Call({e.Value(), Env().Null()});
};