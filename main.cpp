#include <cstdio>
#include "common.h"
#include "class.h"
#include "student.h"
#include "solution.h"
#include <iostream>
#include <fstream>
#include <string>

//#define DEBUG 1

int Student::s_numSubject = 3;

int main(){
  #ifdef DEBUG
  std::string filename;
  std::cout << "Please input filename: ";
  std::cin >> filename;
  
  std::ifstream datafile;
  datafile.open(filename, std::ios::in);
  
  int numStudents, numClasses, numSubjects;
  datafile >> numStudents >> numClasses >> numSubjects;
  std::cout << numStudents << " " << numClasses << std::endl;
  
  Solution *res = new Solution;
  res->init(numClasses);
  
  Student::s_numSubject = numSubjects;
  Student *s;
  for(int i = 0; i < numStudents; ++i){
    s = new Student();
    datafile >> *s;
    res->addStudentAndSetClass(s);
    //std::cout << *s;
  }
  datafile.close();
  
  // test output
  
  std::cout << setlocale(LC_ALL, NULL) << std::endl;
  std::cout.imbue(std::locale());
  std::cout << u8"测试" << std::endl;
  std::ofstream outfile;
  outfile.open("output.txt", std::ios::out);
  outfile << *res;
  outfile.close();
  
  srand((unsigned int)time(NULL));
  #else
  // read in student data
  // run SA
  // print results
  std::string filename;
  std::cout << "Please input filename: ";
  std::cin >> filename;
  
  std::ifstream datafile;
  datafile.open(filename, std::ios::in);
  
  int numStudents, numClasses, numSubjects;
  datafile >> numStudents >> numClasses >> numSubjects;
  std::cout << numStudents << " " << numClasses << std::endl;
  
  Solution *res = new Solution;
  res->init(numClasses);
  
  Student::s_numSubject = numSubjects;
  Student *s;
  for(int i = 0; i < numStudents; ++i){
    s = new Student();
    datafile >> *s;
    res->addStudentAndSetClass(s);
    //std::cout << *s;
  }
  datafile.close();
  #endif
  return 0;
}
