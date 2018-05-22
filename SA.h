#include "common.h"

template<typename T>
class SA{
  private:
  double m_initTemp;
  double m_alpha; // 0 < alpha < 1 drop temperature
  double m_stopTemp;
  double func;
  double temp;
  int steps;
  public:
  SA(double initTemp, double alpha, double stopTemp);
  void run(T& target);
};

template<typename T>
SA<T>::SA(double initTemp, double alpha, double stopTemp): m_initTemp(initTemp), m_alpha(alpha), m_stopTemp(stopTemp){
  func = 0;
  steps = 0;
  temp = m_initTemp;
}

template<typename T>
void SA<T>::run(T& target){
  while(true){
    if(temp <= m_stopTemp){
      return;
    }
  }
}