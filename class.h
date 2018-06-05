#ifndef CLASS_H_
#define CLASS_H_
#include "common.h"
#include "student.h"
#include <list>
#include <vector>
class Class{
  private:
  std::list<Student *> m_students;
  int nMale;
  int nFemale;

  public:
  Class();
  ~Class();

  // Return the number of male/female students in this class
  inline int countMale(){
    return nMale;
  }
  inline int countFemale(){
    return nFemale;
  }

  void deleteAllMembers();

  void appendAndSetClass(Student *t);
  
  Student * popRandomFreeElement();

  void removeStudent(Student *t);

  void fillAvgScoreVector(std::vector<double> &res);
  
  //friend std::wostream & operator << (std::wostream & wos, const Class &c);
  friend std::ostream & operator << (std::ostream & os, const Class &c);
};
#endif
