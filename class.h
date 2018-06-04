#ifndef CLASS_H_
#define CLASS_H_
#include "common.h"
#include "student.h"
#include <list>
#include <vector>
class Class{
  private:
  std::list<Student *> m_students;
  public:
  Class();
  ~Class();
  void appendAndSetClass(Student *t);
  
  Student * popRandomFreeElement();

  void removeStudent(Student *t);

  void fillAvgScoreVector(std::vector<double> &res);
  
  //friend std::wostream & operator << (std::wostream & wos, const Class &c);
  friend std::ostream & operator << (std::ostream & os, const Class &c);
};
#endif
