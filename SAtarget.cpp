#include "SAtarget.h"
#include <cstdlib>
#include <cmath>
#define DEBUG
#ifdef DEBUG
#include <cstdio>
#endif

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
    #ifdef DEBUG
    fprintf(stderr, "Start: F = %lf\n", func);
    #endif
    double newfunc;
    bool accept = false;
    for(int i = 0; i < 500; ++i){
      applyRandomMove();
      newfunc = evalEntropy();
      if(newfunc < func){
        // always accept
        func = newfunc;
        #ifdef DEBUG
        fprintf(stderr, "F = %lf\n", func);
        #endif
      }
      else{
        accept = (((double) rand() / (RAND_MAX)) < exp((func - newfunc) / temp));
        if(accept){
          func = newfunc;
          #ifdef DEBUG
          fprintf(stderr, "F = %lf, *accepted\n", func);
          #endif
        }
        else{
          undoLastMove();
          #ifdef DEBUG
          fprintf(stderr, "F = %lf, *rejected\n", newfunc);
          #endif
        }
      }
    }

    // temperature declines
    temp *= m_alpha;
  }
}

#ifdef DEBUG
#undef DEBUG
#endif