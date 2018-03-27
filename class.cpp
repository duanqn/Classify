#include "class.h"
#include <windows.h>

Class::Class(){
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

Class::~Class(){
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
    throw E_FAIL; // all elements are pinned
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
  return *res;
}

/*
std::wostream & operator << (std::wostream & wos, const Class &c){
  for(auto it = c.m_students.begin(); it != c.m_students.end(); ++it){
    wos << **it;
  }
  return wos;
}
*/

std::ostream & operator << (std::ostream & os, const Class &c){
  for(auto it = c.m_students.begin(); it != c.m_students.end(); ++it){
    os << **it;
  }
  return os;
}
