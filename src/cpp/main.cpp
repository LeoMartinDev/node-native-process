#include <napi.h>
#include <stdio.h>
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
}

std::string GetProcessesByName(const std::string &processName)
{
  listdir();
  return "Hello World";
}

Napi::String GetProcessesByNameWrap(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (info.Length() < 1 || !info[0].IsString())
  {
    Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
  }

  std::string processName = info[0].As<Napi::String>();

  std::string returnValue = GetProcessesByName(processName);

  return Napi::String::New(env, returnValue);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("getProcessesByName", Napi::Function::New(env, GetProcessesByNameWrap));
  return exports;
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports)
{
  Init(env, exports);
  return exports;
}

NODE_API_MODULE(testaddon, InitAll)