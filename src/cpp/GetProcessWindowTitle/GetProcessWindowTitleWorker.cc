#include "GetProcessWindowTitleWorker.hpp"

GetProcessWindowTitleWorker::GetProcessWindowTitleWorker(Napi::Function &callback, int processId)
    : AsyncWorker(callback), processId(processId) {}

GetProcessWindowTitleWorker::~GetProcessWindowTitleWorker() {}

void GetProcessWindowTitleWorker::Execute()
{
  try
  {
    this->result = GetProcessWindowTitle(this->processId);
  }
  catch (const std::exception &error)
  {
    this->SetError(error.what());
  }
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