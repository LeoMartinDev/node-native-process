#include <napi.h>
/* #include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>

#include <stdio.h>
#include <dirent.h>

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int listdir()
{
  struct dirent *entry;
  DIR *dp;

  dp = opendir("/proc");
  if (dp == NULL)
  {
    perror("opendir: Path does not exist or could not be read.");
    return -1;
  }

  while ((entry = readdir(dp)))
  {
    if (is_number(entry->d_name))
    {

      char p[256];
      sprintf(p, sizeof(p), "/proc/%d/cmdline", entry->d_name);
      FILE *file = fopen(p, "r");
      if (file == NULL)
      {
        perror(p);
        return 0;
      }
      if (file)
      {
        int c;
        while ((c = getc(file)) != EOF)
          putchar(c);
        fclose(file);
      }
    }
  }
  closedir(dp);
  return 0;
} */
  #include <cstdio>
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <vector>

/* std::vector<int> GetProcessesByName(const std::string &processName)
{
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    std::vector<int> pids;

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (stricmp(entry.szExeFile, "dofus.exe") == 0)
            {  
                pids.push_back(entry.th32ProcessID);
            }
        }
    }

  CloseHandle(snapshot);
  return pids;
}

Napi::Array GetProcessesByNameWrap(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (info.Length() < 1 || !info[0].IsString())
  {
    Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
  }

  std::string processName = info[0].As<Napi::String>();
  std::vector<int> pids = GetProcessesByName(processName);
  Napi::Array returnValue = Napi::Array::New(env);

  for (int i = 0; i < pids.size(); i++) {
    std::cout << pids.at(i) << std::endl;
    returnValue[i] = Napi::Number::New(env, pids.at(i));
  }
  return returnValue;
} */

#include <napi.h>
#include <chrono>
#include <thread>
#include <cstdio>
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <vector>

std::vector<int> GetProcessesByName(const std::string &processName)
{
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    std::vector<int> pids;

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (stricmp(entry.szExeFile, processName.c_str()) == 0)
            {  
                pids.push_back(entry.th32ProcessID);
            }
        }
    }

  CloseHandle(snapshot);
  return pids;
}

class GetProcessesByNameWorker : public Napi::AsyncWorker {
    public:
        GetProcessesByNameWorker(Napi::Function& callback, std::string& processName)
        : AsyncWorker(callback), processName(processName) {}

        ~GetProcessesByNameWorker() {}
    void Execute() {
        this->result = GetProcessesByName(this->processName);
    }

    void OnOK() {
      Napi::Env env = Env();
      Napi::Array returnValue = Napi::Array::New(env);

      for (int i = 0; i < this->result.size(); i++) {
          returnValue[i] = Napi::Number::New(env, this->result.at(i));
      }

      Callback().MakeCallback(
        Receiver().Value(),
        {
          env.Null(),
          returnValue,
        }
      );
    }

    void OnError(const Napi::Error& e) {
      Napi::Env env = Env();

      Callback().MakeCallback(
        Receiver().Value(),
        {
          e.Value(),
          env.Null()
        }
      );
    }

    private:
        std::string processName;
        std::vector<int> result;
};

void GetProcessesByNameCallback(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 2) {
        Napi::TypeError::New(env, "Invalid argument count").ThrowAsJavaScriptException();
        return;
    }
    if (info.Length() < 1 || !info[0].IsString())
    {
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
    }
    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "Invalid argument types").ThrowAsJavaScriptException();
        return;
    }
    if (!info[1].IsFunction()) {
        Napi::TypeError::New(env, "Invalid argument types").ThrowAsJavaScriptException();
        return;
    }
    Napi::Function cb = info[1].As<Napi::Function>();
    std::string processName = info[0].As<Napi::String>();

    (new GetProcessesByNameWorker(cb, processName))->Queue();
}

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
    Napi::Function::New(env, GetProcessesByNameCallback)
  );
  return exports;
}

NODE_API_MODULE(testaddon, InitAll)