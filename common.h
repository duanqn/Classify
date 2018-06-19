#ifndef COMMON_H_
#define COMMON_H_
#include <string>
#include "utf8.h"
#include "errcode.h"
#include "datafield.h"
//#define NSUBJECT 3

#define INIT_ACCEPTANCE 0.9
#define GENDER_WEIGHT 5
#define TOTAL_WEIGHT 1.0
#define INIT_TEMP 1
#define TEMP_DROP_RATE 0.97
#define STOP_TEMP 0.001


const int n_instance = 4;
const char cg_in_delimiter = ',';  // delimiter for CSV
const char cg_out_delimiter = ' ';
const enum DataType cg_student_field_ordered[] = {
  INFO_GB2312,         // 姓名
  GENDER,       // 性别
  INFO_UNIQUE,  // 学号
  SCORE,        // 语文
  SCORE,        // 数学
  SCORE,        // 英语
  DUMP          // 总分
};

std::string toUTF8String(const wchar_t * str, int len);
std::string toUTF8String(const std::wstring& str);
std::string toGB2312String(const wchar_t * str, int len);
std::string GB2312toUTF8(const std::string& str);
int randint(int upperbound);
#endif
