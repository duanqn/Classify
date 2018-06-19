#include "student.h"
#include <iostream>
#include <cassert>
#include "stringsplitter.h"

int Student::serial = 0;
int Student::s_numSubject = -1;  // default value is useless

Student::Student(){
  m_serial = Student::serial++; // This is not multithread-safe
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
    s.m_fields[i].fromString(segments[i], cg_student_field_ordered[i]);
  }
  // TODO: sort entries and set infoloc, genderloc, scoreloc
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
