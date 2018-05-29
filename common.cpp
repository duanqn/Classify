#include <cstdlib>
#include "common.h"


int randint(int upperbound){
  return (int)(rand()/(double)RAND_MAX * (upperbound - 1));
}

std::string GB2312toUTF8(const std::string& str){
  int length = str.size() + 1;  // '\0'
  char *tmp = new char[2 * length]; // UTF-8 encoding is likely to have greater length
  gb_to_utf8(str.c_str(), tmp, 2 * length);
  std::string res = std::string(tmp);
  delete []tmp;
  return res;
}

#if 0
#ifdef _WIN32
#include <windows.h>
std::string toUTF8String(const wchar_t * str, int len){
  // Get the length of new string first
  int nChars = WideCharToMultiByte(CP_UTF8, 0, str, len, NULL, 0, NULL, NULL);
  if(nChars == 0){
    return std::string("");
  }
  
  std::string newBuffer;
  newBuffer.resize(nChars);
  WideCharToMultiByte(CP_UTF8, 0, str, len, const_cast<char *>(newBuffer.c_str()), nChars, NULL, NULL);
  
  return newBuffer;
}

std::string toGB2312String(const wchar_t * str, int len){
  // Get the length of new string first
  int nChars = WideCharToMultiByte(936, 0, str, len, NULL, 0, NULL, NULL);
  if(nChars == 0){
    return std::string("");
  }
  
  std::string newBuffer;
  newBuffer.resize(nChars);
  WideCharToMultiByte(936, 0, str, len, const_cast<char *>(newBuffer.c_str()), nChars, NULL, NULL);
  
  return newBuffer;
}

std::string GB2312toUTF8(const std::string& str){
  int nChars = MultiByteToWideChar(936, 0, str.c_str(), str.size(), NULL, 0);
  if(nChars == 0){
    return std::string("");
  }
  
  std::wstring newBuffer;
  newBuffer.resize(nChars);
  MultiByteToWideChar(936, 0, str.c_str(), str.size(), const_cast<wchar_t *>(newBuffer.c_str()), nChars);
  
  return toUTF8String(newBuffer);
}

std::string toUTF8String(const std::wstring& str)
{
	return toUTF8String(str.c_str(), (int)str.size());
}

std::string toGB2312String(const std::wstring& str)
{
	return toGB2312String(str.c_str(), (int)str.size());
}

#elif __linux__
std::string toUTF8String(const std::wstring& str)
{
	return toUTF8String(str.c_str(), (int)str.size());
}

std::string toGB2312String(const std::wstring& str)
{
	return toGB2312String(str.c_str(), (int)str.size());
}

#else
  #error OS not supported
#endif

#endif