#include "student.h"
#include <iostream>
#include <cassert>
#include "stringsplitter.h"

int Student::serial = 0;
int Student::s_numSubject = -1;  // default value is useless

Student::Student(){
  m_serial = Student::serial++; // This is not multithread-safe
  m_genderloc = 0;
  m_scoreloc = 0;
}

Student::~Student(){
}

void Student::fillScoreVector(std::vector<double> &res){
  res.clear();
  for(int i = 0; i < s_numSubject; ++i){
    res.push_back(getScore(i));
  }
}

std::istream & operator >>(std::istream &is, Student &s){
  std::string line;
  std::getline(is, line);
  std::vector<std::string> segments;
  split(line, segments, cg_in_delimiter);
  unsigned int nFields = sizeof(cg_student_field_ordered) / sizeof(DataType);
  if(nFields != segments.size()){
    throw duanqn::E_BADFORMAT;
  }
  for(unsigned int i = 0; i < nFields; ++i){
    s.m_fields.push_back(fromString(segments[i], cg_student_field_ordered[i]));
  }
  // TODO: sort entries and set infoloc, genderloc, scoreloc
  for(int i = 0; i < nFields - 1; ++i){
    for(int j = i + 1; j < nFields; ++j){
      if(int(s.m_fields[i].type) > int(s.m_fields[j].type)){
        DataField t = std::move(s.m_fields[j]);
        s.m_fields[j] = std::move(s.m_fields[i]);
        s.m_fields[i] = std::move(t);
      }
    }
  }
  for(int i = nFields - 1; i >= 0; --i){
    switch(s.m_fields[i].type){
    case DataType::GENDER:
      s.m_genderloc = i;
      break;
    case DataType::SCORE:
      s.m_scoreloc = i;
      break;
    }
  }
  return is;
}

/*
std::wostream & operator << (std::wostream &wos, Student &s){
  wos << s.m_name << " ";
  if(s.m_gender == Student::Male){
    wos << "M ";
  }
  else{
    wos << "F ";
  }
  for(int i = 0; i < s.m_score.size(); ++i){
    wos << s.m_score[i] << " ";
  }
  wos << std::endl;
  return wos;
}
*/

std::ostream & operator << (std::ostream &os, const Student &s){
  unsigned int nFields = sizeof(cg_student_field_ordered) / sizeof(DataType);
  for(unsigned int i = 0; i < nFields; ++i){
    os << s.m_fields[i].toUTF8String() << cg_out_delimiter;
  }
  os << std::endl;
  return os;
}

bool Student::isPinned() const{
  return false;
}

bool Student::pin(){
  return false; // not implemented
}
