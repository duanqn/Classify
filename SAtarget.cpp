#include "SAtarget.h"
#include <cstdlib>
#include <cmath>
//#define DEBUG
#ifdef DEBUG
#include <cstdio>
#endif

SAtarget::SAtarget(double initTemp, double alpha, double stopTemp, int Markov):
  m_initTemp(initTemp), m_alpha(alpha), m_stopTemp(stopTemp), m_MarkovLen(Markov){
  func = 0;
  temp = initTemp;
  steps = 0;
}

SAtarget::~SAtarget(){}

bool SAtarget::accept(double oldval, double newval, double temperature){
  double randval = rand() / (double)RAND_MAX;
  if(newval < oldval){
    return true;
  }
  else{
    return randval < exp((oldval - newval) / temperature);
  }
}

void SAtarget::run(){
  while(true){
    if(temp <= m_stopTemp){
      break;
    }

    func = evalEntropy();
    #ifdef DEBUG
    fprintf(stderr, "Start: F = %lf\n", func);
    #endif
    double newfunc;
    bool accept = false;
    for(int i = 0; i < m_MarkovLen; ++i){
      applyRandomMove();
      newfunc = evalEntropy();
      if(SAtarget::accept(func, newfunc, temp)){
        func = newfunc;
        #ifdef DEBUG
        fprintf(stderr, "F => %lf\n", func);
        #endif
      }
      else{
        undoLastMove();
        #ifdef DEBUG
        fprintf(stderr, "F = %lf, *rejected\n", newfunc);
        #endif
      }
    }

    // temperature declines
    temp *= m_alpha;
  }
}

#ifdef DEBUG
#undef DEBUG
#endif