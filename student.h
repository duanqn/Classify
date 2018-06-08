#ifndef STUDENT_H_
#define STUDENT_H_
#include "common.h"
#include <string>
#include <vector>
class Class;
class Student{
  public:
  enum Gender {Male, Female};
  static int s_numSubject;
  
  protected:
  
  static int serial;
  int m_serial;
  
  //  学生信息：
  //  姓名、性别、成绩
  std::string m_name;
  Gender m_gender;
  std::vector<double> m_score;
  
  // ban copy-constructors
  Student(const Student &);
  Student& operator = (const Student &);
  public:
  Student();
  ~Student();
  double getScore(int subject) const {
    return m_score[subject];
  }
  void setScore(int subject, double val){
    m_score[subject] = val;
  }
  bool isMale() const {
    return m_gender == Male;
  }

  inline const Gender getGender() const {
    return m_gender;
  }

  inline const std::string getName() const {
    return m_name;
  }

  void fillScoreVector(std::vector<double> &res);
  
  virtual bool isPinned() const;
  virtual bool pin(); // returns successful or not
  
  friend std::istream & operator >> (std::istream &is, Student &s);
  friend std::ostream & operator << (std::ostream &os, const Student &s);
};
#endif
