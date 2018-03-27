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
void SA::run(T& target){
  while(true){
    if(temp <= m_stopTemp){
      return;
    }
    
  }
}