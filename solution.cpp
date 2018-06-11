#include "solution.h"
#include <iostream>
#include <cstdlib>

#define DEBUG
#ifdef DEBUG
#include <cstdio>
#endif

Solution::Solution(double initTemp, double alpha, double stopTemp, int Markov): SAtarget(initTemp, alpha, stopTemp, Markov){
  nextAppendPos = 0;
  lastmove_1 = lastmove_2 = nullptr;
  lastmove_class_1 = lastmove_class_2 = nullptr;
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
    throw duanqn::E_INVALIDARG;
  }
  return nullptr;
}

void Solution::init(int numClass){
  if(numClass <= 0){
    throw duanqn::E_INVALIDARG;
  }
  for(int i = 0; i < numClass; ++i){
    vClass.push_back(new Class);  // may throw exception if 'new' fails
  }
}

void Solution::addStudent(Student *s){
  if(s == nullptr){
    throw duanqn::E_INVALIDARG;
  }
  vClass[nextAppendPos]->append(s);
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
    catch(duanqn::ERRCODE &code){
      successful = false;
      continue;
    }
    
    try{
      s2 = vClass[c2]->popRandomFreeElement();
    }
    catch(duanqn::ERRCODE &code){
      vClass[c1]->append(s1);  // undo pop
      successful = false;
      continue;
    }
    
    vClass[c1]->append(s2);
    vClass[c2]->append(s1);  // exchange
  }while(!successful);  // TODO: abort after n failures

  lastmove_1 = s1;
  lastmove_class_1 = vClass[c2];
  lastmove_2 = s2;
  lastmove_class_2 = vClass[c1];
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
  std::vector<double> avgScore;
  std::vector<double> s2Score;
  double res;

  for(int i = 0; i < vClass.size(); ++i){
    avgMNum += vClass[i]->countMale();
    avgFNum += vClass[i]->countFemale();
  }
  avgMNum /= vClass.size();
  avgFNum /= vClass.size();

  for(int i = 0; i < vClass.size(); ++i){
    s2MNum += (vClass[i]->countMale() - avgMNum) * (vClass[i]->countMale() - avgMNum);
    s2FNum += (vClass[i]->countFemale() - avgFNum) * (vClass[i]->countFemale() - avgFNum);
  }
  s2MNum /= vClass.size();
  s2FNum /= vClass.size();

  avgScore.resize(Student::s_numSubject, 0);
  s2Score.resize(Student::s_numSubject, 0);
  
  std::vector<std::vector<double> > avg;
  avg.resize(vClass.size());
  for(int i = 0; i < vClass.size(); ++i){
    vClass[i]->fillAvgScoreVector(avg[i]);
  }

  for(int subject = 0; subject < Student::s_numSubject; ++subject){
    for(int i = 0; i < vClass.size(); ++i){
      avgScore[subject] += avg[i][subject];
    }
    avgScore[subject] /= vClass.size();
  }

  for(int subject = 0; subject < Student::s_numSubject; ++subject){
    for(int i = 0; i < vClass.size(); ++i){
      s2Score[subject] += (avg[i][subject] - avgScore[subject]) * (avg[i][subject] - avgScore[subject]);
    }
    s2Score[subject] /= vClass.size();
  }

  // Avg on total
  double avgTotal = 0;
  double s2Total = 0;
  double temp = 0;
  for(int i = 0; i < vClass.size(); ++i){
    for(int subject = 0; subject < Student::s_numSubject; ++subject){
      avgTotal += avg[i][subject];
    }
  }
  avgTotal /= vClass.size();

  for(int i = 0; i < vClass.size(); ++i){
    temp = 0;
    for(int subject = 0; subject < Student::s_numSubject; ++subject){
      temp += avg[i][subject];
    }
    s2Total += (temp - avgTotal) * (temp - avgTotal);
  }
  s2Total /= vClass.size();

  // Compute res based on weights
  res += s2MNum * 5 + s2FNum * 5;
  for(int subject = 0; subject < Student::s_numSubject; ++subject){
    res += s2Score[subject];
  }
  res += s2Total;

  return res;
}

void Solution::undoLastMove(){
  lastmove_class_1->removeStudent(lastmove_1);
  lastmove_class_2->removeStudent(lastmove_2);
  lastmove_class_1->append(lastmove_2);
  lastmove_class_2->append(lastmove_1);
}

double Solution::testAcceptance(){
  int number = 1000;
  double func_1 = evalEntropy();
  double func_2 = 0;
  int count = 0;
  for(int i = 0; i < number; ++i){
    applyRandomMove();
    func_2 = evalEntropy();
    if(accept(func_1, func_2, m_initTemp)){
      ++count;
    }
    undoLastMove();
  }
  return count / (double)number;
}

void Solution::run(){
  while(testAcceptance() < 0.9){
    m_initTemp *= 1.1;
  }
  #ifdef DEBUG
  printf("Init temp: %lf\n", m_initTemp);
  #endif
  SAtarget::run();
}

void Solution::deleteAllStudents(){
  for(int i = 0; i < vClass.size(); ++i){
    vClass[i]->deleteAllMembers();
  }
}

void Solution::randomShuffle(){
  if(vClass.size() > 0){
    int studentnum = vClass[0]->countMale() + vClass[0]->countFemale();
    for(int i = 0; i < studentnum * vClass.size() * studentnum * vClass.size() / 2.0; ++i){
      applyRandomMove();
    }
  }
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
  #ifdef DEBUG
  os << u8"熵： " << s.func << std::endl;
  #endif
  return os;
}

#ifdef DEBUG
#undef DEBUG
#endif
