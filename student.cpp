#include "student.h"
#include <iostream>
#include <cassert>

int Student::serial = 0;

Student::Student(int subject): m_numSubject(subject){
  m_class = nullptr;
  m_serial = Student::serial++; // This is not multithread-safe
}

Student::~Student(){
}

std::istream & operator >>(std::istream &is, Student &s){
  is >> s.m_name;
  int tmp;
  is >> tmp;
  if(tmp == 1){
    s.m_gender = Student::Male;
  }
  else{
    s.m_gender = Student::Female;
  }
  
  s.m_score.clear();
  double tmpscore;
  for(int i = 0; i < s.m_numSubject; ++i){
    is >> tmpscore;
    s.m_score.push_back(tmpscore);
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

std::ostream & operator << (std::ostream &os, Student &s){
  //os << (s.m_name) << " ";
  os << GB2312toUTF8(s.m_name) << " ";
  if(s.m_gender == Student::Male){
    os << "M ";
  }
  else{
    os << "F ";
  }
  for(int i = 0; i < s.m_score.size(); ++i){
    os << s.m_score[i] << " ";
  }
  os << std::endl;
  return os;
}

bool Student::isPinned(){
  return false;
}

bool Student::pin(){
  return false; // not implemented
}
