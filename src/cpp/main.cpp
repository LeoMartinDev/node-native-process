#include <napi.h>
#include "GetProcessesByName/getProcessesByName_main.hpp"
#include "GetProcessWindowTitle/getProcessWindowTitle_main.hpp"
#include "SetProcessToForeground/setProcessToForeground_main.hpp"

Napi::Object InitAll(Napi::Env env, Napi::Object exports)
{
  exports.Set(
      Napi::String::New(env, "setProcessToForeground"),
      Napi::Function::New(env, SetProcessToForegroundCallback));
  exports.Set(
      Napi::String::New(env, "getProcessesByName"),
      Napi::Function::New(env, GetProcessesByNameCallback));
  exports.Set(
      Napi::String::New(env, "getProcessWindowTitle"),
      Napi::Function::New(env, GetProcessWindowTitleCallback));
  return exports;
}

NODE_API_MODULE(addon, InitAll)