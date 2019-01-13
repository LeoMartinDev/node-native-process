#include <napi.h>
#include "GetProcessesByName/getProcessesByName_main.hpp"
#include "GetProcessWindowTitle/getProcessWindowTitle_main.hpp"

/* Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("getProcessesByName", Napi::Function::New(env, GetProcessesByNameWrap));
  return exports;
} */

Napi::Object InitAll(Napi::Env env, Napi::Object exports)
{
  //Init(env, exports);
  exports.Set(
      Napi::String::New(env, "getProcessesByName"),
      Napi::Function::New(env, GetProcessesByNameCallback));
  exports.Set(
      Napi::String::New(env, "getProcessWindowTitle"),
      Napi::Function::New(env, GetProcessWindowTitleCallback));
  return exports;
}

NODE_API_MODULE(addon, InitAll)