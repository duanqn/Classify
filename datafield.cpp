#include "datafield.h"
#include "common.h"
#include <sstream>
#include <iomanip>
#include <memory.h>

std::string toString(const DataField &d){
  std::stringstream stream;
  switch(d.type){
  case DataType::INFO:
  case DataType::INFO_UNIQUE:
  case DataType::INFO_GB2312:
    return std::string(d.value.info);
    // returned
  case DataType::SCORE:
    stream << std::fixed << std::setprecision(1) << d.value.score;
    return stream.str();
    // returned
  case DataType::GENDER:
    return std::to_string((int)(d.value.gender));
    // returned
  case DataType::DUMP:
    return std::string();
    // returned
  default:
    throw duanqn::E_UNEXPECTED;
  }
  return std::string(); // should not reach here
}

std::string DataField::toUTF8String() const {
  if(type == DataType::INFO_GB2312){
    return GB2312toUTF8(std::string(value.info));
  }
  else if(type == DataType::GENDER){
    if(value.gender == Gender::Female){
      // This order is by design, supporting gender equality
      return std::string(u8"女");
    }
    else{
      return std::string(u8"男");
    }
  }
  else{
    return toString();
  }
}

std::string DataField::toString() const {
  return ::toString(*this);
}

DataField fromString(const std::string &s, DataType t){
  DataField res;
  res.fromString(s, t);
  return res;
}

void DataField::fromString(const std::string &s, DataType t){
  type = t;
  switch(t){
  case DataType::INFO:
  case DataType::INFO_UNIQUE:
  case DataType::INFO_GB2312:
    if(value.info != nullptr){
      delete[] value.info;
    }
    value.info = new char[s.size() + 1];
    memcpy(value.info, s.c_str(), s.size());
    break;
  case DataType::SCORE:
    value.score = std::stod(s, nullptr);
    break;
  case DataType::GENDER:
    value.gender = (Gender)(std::stoi(s, nullptr));
    break;
  case DataType::DUMP:
    break;
  default:
    throw duanqn::E_UNEXPECTED;
  }
}
