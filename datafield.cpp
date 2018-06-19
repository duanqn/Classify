#include "datafield.h"
#include "common.h"

std::string toString(const DataField &d){
  switch(d.type){
  case DataType::INFO:
  case DataType::INFO_UNIQUE:
  case DataType::INFO_GB2312:
    return d.value.info;
    // returned
  case DataType::SCORE:
    return std::to_string(d.value.score);
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
    return GB2312toUTF8(value.info);
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
  switch(t){
  case DataType::INFO:
  case DataType::INFO_UNIQUE:
  case DataType::INFO_GB2312:
    value.info = s;
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
