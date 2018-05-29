#ifndef COMMON_H_
#define COMMON_H_
#include <string>
#include "utf8.h"
//#define NSUBJECT 3

namespace duanqn{
  
  typedef int ERRCODE;
  const int S_OK = 0;
  const int S_FALSE = S_OK + 1;
  const int E_FAIL = S_FALSE + 1;
  const int E_INDEXOVERFLOW = E_FAIL + 1;
  const int E_MEM = E_INDEXOVERFLOW + 1;
  const int E_INVALIDARG = E_MEM + 1;
  const int E_TRIGGER = 0xDEADBEEF;
  const int E_UNEXPECTED = 0x77777777;
  
}




std::string toUTF8String(const wchar_t * str, int len);
std::string toUTF8String(const std::wstring& str);
std::string toGB2312String(const wchar_t * str, int len);
std::string GB2312toUTF8(const std::string& str);
int randint(int upperbound);
#endif
