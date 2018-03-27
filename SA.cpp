#include "SA.h"

SA::SA(double initTemp, double alpha, double stopTemp): m_initTemp(initTemp), m_alpha(alpha), m_stopTemp(stopTemp){
  func = 0;
  steps = 0;
  temp = m_initTemp;
}