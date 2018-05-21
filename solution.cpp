#include "solution.h"
#include <iostream>
#include <windows.h>  // for HRESULT
Solution::Solution(){
  nextAppendPos = 0;
}

Solution::~Solution(){
  for(int i = 0; i < vClass.size(); ++i){
    if(vClass[i] != NULL){
      delete vClass[i];
    }
  }
}

Class * Solution::accessClass(int i){
  if(i >= 0 && i < vClass.size()){
    return vClass[i];
  }
  else{
    throw E_INVALIDARG;
  }
  return nullptr;
}

void Solution::init(int numClass){
  if(numClass <= 0){
    throw E_INVALIDARG;
  }
  for(int i = 0; i < numClass; ++i){
    vClass.push_back(new Class);  // may throw exception if 'new' fails
  }
}

void Solution::addStudentAndSetClass(Student *s){
  if(s == nullptr){
    throw E_INVALIDARG;
  }
  vClass[nextAppendPos]->appendAndSetClass(s);
  ++nextAppendPos;
  if(nextAppendPos == vClass.size()){
    nextAppendPos = 0;
  }
}

void Solution::applyRandomMove(){
  int c1, c2;
  Student *s1 = nullptr, *s2 = nullptr;
  bool successful;
  do{
    successful = true;
    c1 = rand() % vClass.size();
    do{
      c2 = rand() % vClass.size();
    }while(c1 == c2);
    
    
    try{
      s1 = vClass[c1]->popRandomFreeElement();
    }
    catch(HRESULT &code){
      successful = false;
      continue;
    }
    
    try{
      s2 = vClass[c2]->popRandomFreeElement();
    }
    catch(HRESULT &code){
      vClass[c1]->appendAndSetClass(s1);  // undo pop
      successful = false;
      continue;
    }
    
    vClass[c1]->appendAndSetClass(s2);
    vClass[c2]->appendAndSetClass(s1);  // exchange
  }while(!successful);  // TODO: abort after n failures
}

double Solution::evalEntropy(){
  //要求：
  //男女生数量
  //各科平均分
  //总平均分
  //以上几项尽量接近
  double entropy = 0;
  double s2MNum = 0, s2FNum = 0;
  double avgMNum = 0, avgFNum = 0;
  
}

void Solution::output(FILE *f){
  // TODO
}

/*
std::wostream & operator << (std::wostream &wos, const Solution &s){
  wos << L">>>>>方案开始>>>>>" << std::endl;
  for(int i = 0; i < s.vClass.size(); ++i){
    wos << "=====" << i << L"班" << "=====" << std::endl;
    wos << *(s.vClass[i]);
  }
  wos << L"<<<<<方案结束<<<<<" << std::endl;
  return wos;
}
*/

std::ostream & operator << (std::ostream &os, const Solution &s){
  os << u8">>>>>方案开始>>>>>" << std::endl;
  for(int i = 0; i < s.vClass.size(); ++i){
    os << "=====" << i << u8"班" << "=====" << std::endl;
    os << *(s.vClass[i]);
  }
  os << u8"<<<<<方案结束<<<<<" << std::endl;
  return os;
}
