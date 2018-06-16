#ifndef SOLUTION_H_
#define SOLUTION_H_
#include <vector>
#include "common.h"
#include "class.h"
#include "SAtarget.h"
class Solution: public SAtarget{
  private:
  std::vector<Class *> vClass;
  int nextAppendPos;
  
  double m_weightGenderInequality;
  std::vector<double> m_weightMaleAvg;
  std::vector<double> m_weightFemaleAvg;
  std::vector<double> m_weightTotalAvg;

  Student *lastmove_1;
  Class *lastmove_class_1;
  Student *lastmove_2;
  Class *lastmove_class_2;

  double testAcceptance();
  
  public:
  Solution(double initTemp, double alpha, double stopTemp, int Markov);
  ~Solution();

  //  May throw exception
  //  E_INDEXOVERFLOW
  //  E_INVALIDARG
  Class * accessClass(int i);
  
  //  May throw exception
  //  E_INVALIDARG
  void init(int numClass);
  
  void output(FILE *f);
  
  void addStudent(Student *s);

  void deleteAllStudents();

  void randomShuffle();

  inline double getEntropy(){
    return func;
  }

  // inherited
  virtual double evalEntropy();
  virtual void applyRandomMove();
  virtual void undoLastMove();
  virtual void run();

  double calcMinEntropy() const;
  
  //friend std::wostream & operator << (std::wostream &os, const Solution &s);
  friend std::ostream & operator << (std::ostream &os, const Solution &s);
};
#endif
