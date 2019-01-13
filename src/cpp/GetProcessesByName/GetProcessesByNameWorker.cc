#include "GetProcessesByNameWorker.hpp"

GetProcessesByNameWorker::GetProcessesByNameWorker(Napi::Function &callback, const std::string &processName)
    : AsyncWorker(callback), processName(processName) {}

GetProcessesByNameWorker::~GetProcessesByNameWorker() {}

void GetProcessesByNameWorker::Execute()
{
  this->result = GetProcessesByName(this->processName);
}

void GetProcessesByNameWorker::OnOK()
{
  Napi::HandleScope scope(Env());
  Napi::Array returnValue = Napi::Array::New(Env());

  for (int i = 0; i < this->result.size(); i++)
  {
    returnValue[i] = Napi::Number::New(Env(), this->result.at(i));
  }
  Callback().Call({Env().Null(), returnValue});
}

void GetProcessesByNameWorker::OnError(const Napi::Error &e)
{
  Napi::HandleScope scope(Env());

  Callback().Call({e.Value(), Env().Null()});
};