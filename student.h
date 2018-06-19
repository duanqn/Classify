#ifndef STUDENT_H_
#define STUDENT_H_
#include "gender.h"
#include "common.h"
#include <string>
#include <vector>
#include "datafield.h"
class Class;
class Student{
  public:
  static int s_numSubject;
  
  protected:
  
  static int serial;
  int m_serial;
  
  //  学生信息：
  //  姓名、性别、成绩
  /*
  std::string m_name;
  Gender m_gender;
  std::vector<double> m_score;
  */
  std::vector<DataField> m_fields;
  int m_infoloc;
  int m_genderloc;
  int m_scoreloc;
  
  // ban copy-constructors
  Student(const Student &);
  Student& operator = (const Student &);
  public:
  Student();
  ~Student();
  double getScore(int subject) const {
    if(m_fields[m_scoreloc + subject].type != DataType::SCORE){
      throw duanqn::E_BADFORMAT;
    }
    return m_fields[m_scoreloc + subject].value.score;
  }
  void setScore(int subject, double val){
    if(m_fields[m_scoreloc + subject].type != DataType::SCORE){
      throw duanqn::E_BADFORMAT;
    }
    m_fields[m_scoreloc + subject].value.score = val;
  }
  bool isMale() const {
    if(m_fields[m_genderloc].type != DataType::GENDER){
      throw duanqn::E_BADFORMAT;
    }
    return m_fields[m_genderloc].value.gender == Gender::Male;
  }

  inline const Gender getGender() const {
    if(m_fields[m_genderloc].type != DataType::GENDER){
      throw duanqn::E_BADFORMAT;
    }
    return m_fields[m_genderloc].value.gender;
  }

  void fillScoreVector(std::vector<double> &res);
  
  virtual bool isPinned() const;
  virtual bool pin(); // returns successful or not
  
  friend std::istream & operator >> (std::istream &is, Student &s);
  friend std::ostream & operator << (std::ostream &os, const Student &s);
};
#endif
