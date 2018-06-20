#ifndef DATAFIELD_H_
#define DATAFIELD_H_

#include <string>
#include "gender.h"
#include "errcode.h"
#include <cstdio>

enum DataType{INFO, INFO_UNIQUE, INFO_GB2312, GENDER, SCORE, DUMP};

struct DataContent{
  char * info; // type = info, info_unique or dump
  double score;     // type = score
  Gender gender;    // type = gender
  DataContent(){
    gender = Gender::Male;
    score = 0;
    info = nullptr;
  }
  DataContent(DataContent && d){
    gender = d.gender;
    score = d.score;
    info = d.info;
    d.info = nullptr;
  }
  DataContent& operator = (DataContent && d){
    gender = d.gender;
    score = d.score;
    info = d.info;
    d.info = nullptr;
    return *this;
  }
  ~DataContent(){
    if(info != nullptr){
      delete[] info;
    }
  }
};

struct DataField{
  enum DataType type;
  struct DataContent value;

  DataField(): value(){
    type = DataType::DUMP;
  }
  DataField(DataField && d): value(std::move(d.value)){
    type = d.type;
  }
  DataField& operator = (DataField && d){
    type = d.type;
    value = std::move(d.value);
    return *this;
  }
  ~DataField(){}
  std::string toString() const;
  std::string toUTF8String() const;
  void fromString(const std::string &s, DataType t);
};

std::string toString(const DataField &d);
DataField fromString(const std::string &s, DataType t);

#endif  // DATAFIELD_H_