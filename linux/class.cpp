#include "class.h"
#include <cstdlib>
#include <iostream>

Class::Class(){
  nMale = nFemale = 0;
}

Class::~Class(){
}

void Class::deleteAllMembers(){
  for(auto it = m_students.begin(); it != m_students.end(); ++it){
    delete *it;
  }
}

void Class::append(Student *t){
  if(t->isMale()){
    ++nMale;
    m_students.push_front(t);
  }
  else{
    ++nFemale;
    m_students.push_back(t);
  }
}

Student * Class::popRandomFreeElement(){
  int r;
  auto it = m_students.begin();
  bool found = false;
  for(; it != m_students.end(); ++it){
    if(!((*it)->isPinned())){
      found = true;
      break;
    }
  }
  if(found == false){
    throw duanqn::E_FAIL; // all elements are pinned
  }
  found = false;
  while(!found){  // Inefficient when most students are pinned
    r = rand() % m_students.size();
    it = m_students.begin();
    for(int i = 0; i < r; ++i){
      ++it;
    }
    if(!((*it)->isPinned())){
      found = true;
    }
  }

  Student *res = *it;
  if(res->isMale()){
    --nMale;
  }
  else{
    --nFemale;
  }
  it = m_students.erase(it);
  return res;
}

void Class::fillAvgScoreVector(std::vector<double> &res) const {
  // This function needs to be re-written!
  // Don't use fillScoreVector to get the size
  res.clear();
  res.resize(Student::s_numSubject, 0.0);
  
  std::vector<double> score;
  for(auto it = m_students.begin(); it != m_students.end(); ++it){
    (*it)->fillScoreVector(score);
    for(unsigned i = 0; i < res.size(); ++i){
      res[i] += score[i];
    }
  }

  for(unsigned i = 0; i < res.size(); ++i){
    res[i] /= m_students.size();
  }
}

void Class::removeStudent(Student *t){
  if(t->isMale()){
    --nMale;
  }
  else{
    --nFemale;
  }
  m_students.remove(t);
}

std::ostream & operator << (std::ostream & os, const Class &c){
  if(rand() / (double)RAND_MAX < 0.5){
    os << u8"男生 " << c.nMale << u8" 人" << std::endl;
    os << u8"女生 " << c.nFemale << u8" 人" << std::endl;
  }
  else{
    os << u8"女生 " << c.nFemale << u8" 人" << std::endl;
    os << u8"男生 " << c.nMale << u8" 人" << std::endl;
  }
  os << u8"平均分： ";
  std::vector<double> avgs;
  c.fillAvgScoreVector(avgs);
  double overall = 0;
  for(unsigned i = 0; i < avgs.size(); ++i){
    if(i > 0){
      os << " ";
    }
    overall += avgs[i];
    os << avgs[i];
  }
  os << " " << overall << std::endl;
  for(auto it = c.m_students.begin(); it != c.m_students.end(); ++it){
    os << **it;
  }
  return os;
}
