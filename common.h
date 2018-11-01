#ifndef COMMON_H_
#define COMMON_H_
#include <string>
#include "utf8.h"
#include "errcode.h"
#include "datafield.h"
//#define NSUBJECT 3

#define INIT_ACCEPTANCE 0.9
#define GENDER_WEIGHT 10.0
#define TOTAL_WEIGHT 5.0
#define INIT_TEMP 1
#define TEMP_DROP_RATE 0.97
#define STOP_TEMP 0.001


extern const int n_instance;
extern const char cg_in_delimiter;  // delimiter for CSV
extern const char cg_out_delimiter;
extern enum DataType cg_student_field_ordered[];
extern const unsigned cgu_nFields;

std::string toUTF8String(const wchar_t * str, int len);
std::string toUTF8String(const std::wstring& str);
std::string toGB2312String(const wchar_t * str, int len);
std::string GB2312toUTF8(const std::string& str);
int randint(int upperbound);
#endif
