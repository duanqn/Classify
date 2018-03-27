#ifndef CLASS_H_
#define CLASS_H_
#include "common.h"
#include "Student.h"
#include <list>
class Class{
  private:
  std::list<Student *> m_students;
  // TODO: USE LIST INSTEAD
  public:
  Class();
  ~Class();
  void appendAndSetClass(Student *t);
  
  Student * popRandomFreeElement();
  
  //friend std::wostream & operator << (std::wostream & wos, const Class &c);
  friend std::ostream & operator << (std::ostream & os, const Class &c);
};
#endif
