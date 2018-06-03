#include "class.h"
#include <cstdlib>

Class::Class(){
}

Class::~Class(){
}

void Class::appendAndSetClass(Student *t){
  if(t->isMale()){
    m_students.push_front(t);
  }
  else{
    m_students.push_back(t);
  }
  t->setClass(this);
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
  while(!found){
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
  it = m_students.erase(it);
  return res;
}

void Class::fillAvgScoreVector(std::vector<double> &res){
  // This function needs to be re-written!
  // Don't use fillScoreVector to get the size
  res.clear();
  res.resize(Student::s_numSubject, 0.0);
  
  std::vector<double> score;
  for(auto it = m_students.begin(); it != m_students.end(); ++it){
    (*it)->fillScoreVector(score);
    for(int i = 0; i < res.size(); ++i){
      res[i] += score[i];
    }
  }

  for(int i = 0; i < res.size(); ++i){
    res[i] /= m_students.size();
  }
}

std::ostream & operator << (std::ostream & os, const Class &c){
  for(auto it = c.m_students.begin(); it != c.m_students.end(); ++it){
    os << **it;
  }
  return os;
}
