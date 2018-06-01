#include "SAtarget.h"

SAtarget::SAtarget(double initTemp, double alpha, double stopTemp):
  m_initTemp(initTemp), m_alpha(alpha), m_stopTemp(stopTemp){
  func = 0;
  temp = initTemp;
  steps = 0;
}

SAtarget::~SAtarget(){}

void SAtarget::run(){
  while(true){
    if(temp <= m_stopTemp){
      break;
    }

    func = evalEntropy();
    double newfunc;
    bool accept = false;
    for(int i = 0; i < 500; ++i){
      applyRandomMove();
      newfunc = evalEntropy();
      accept = f(func, newfunc, temp);
      if(!accept){
        undoLastMove();
      }
    }

    // temperature declines
    temp *= m_alpha;
  }
}
