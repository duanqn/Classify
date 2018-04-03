#ifndef STUDENT_H_
#define STUDENT_H_
#include "common.h"
#include <string>
#include <vector>
class Class;
class Student{
  public:
  enum Gender {Male, Female};
  
  protected:
  
  static int serial;
  int m_serial;
  
  int m_numSubject;

  //  学生信息：
  //  姓名、性别、成绩
  std::string m_name;
  Gender m_gender;
  std::vector<double> m_score;
  
  // assigned class
  Class *m_class;
  
  // ban copy-constructors
  Student(const Student &);
  Student& operator = (const Student &);
  public:
  Student(int subject);
  ~Student();
  double getScore(int subject){
    return m_score[subject];
  }
  void setScore(int subject, double val){
    m_score[subject] = val;
  }
  Class* getClass(){
    return m_class;
  }
  void setClass(Class *val){
    m_class = val;
  }
  bool isMale(){
    return m_gender == Male;
  }
  
  virtual bool isPinned();
  virtual bool pin(); // returns successful or not
  
  friend std::istream & operator >> (std::istream &is, Student &s);
  friend std::ostream & operator << (std::ostream &os, Student &s);
};
#endif
