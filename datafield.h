#ifndef DATAFIELD_H_
#define DATAFIELD_H_

#include <string>
#include "gender.h"
#include "errcode.h"

enum DataType{INFO, INFO_UNIQUE, INFO_GB2312, GENDER, SCORE, DUMP};

union DataContent{
  std::string info; // type = info, info_unique or dump
  double score;     // type = score
  Gender gender;    // type = gender
  DataContent(){
    score = 0;
  }
  ~DataContent(){}
};

struct DataField{
  enum DataType type;
  union DataContent value;

  DataField(): value(){
    type = DataType::DUMP;
  }
  ~DataField(){}
  DataField(DataField &&t){
    switch(t.type){
    case SCORE:
      value.score = t.value.score;
      break;
    case GENDER:
      value.gender = t.value.gender;
      break;
    case INFO:
      value.info = std::move(t.value.info);
      break;
    default:
      value.score = 0;
    }
  }
  std::string toString() const;
  std::string toUTF8String() const;
  void fromString(const std::string &s, DataType t);
};

std::string toString(const DataField &d);
DataField fromString(const std::string &s, DataType t);

#endif  // DATAFIELD_H_