#include <cstdio>
#include "common.h"
#include "class.h"
#include "student.h"
#include "solution.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>

//#define DEBUG 1
const int n_instance = 10;

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
  Student::s_numSubject = numSubjects;
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
  
  #else
  srand((unsigned int)time(nullptr));

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
  
  Solution **array = new Solution* [n_instance];
  for(int i = 0; i < n_instance; ++i){
    array[i] = new Solution(500, 0.93, 0.1, 10*numStudents);
    array[i]->init(numClasses);
    array[i]->randomShuffle();
  }
  
  Student::s_numSubject = numSubjects;
  Student *s;
  for(int i = 0; i < numStudents; ++i){
    s = new Student();
    datafile >> *s;
    for(int j = 0; j < n_instance; ++j){
      array[j]->addStudentAndSetClass(s);
    }
    //std::cout << *s;
  }
  datafile.close();

  for(int j = 0; j < n_instance; ++j){
    array[j]->run();
  }

  std::cout << setlocale(LC_ALL, NULL) << std::endl;
  std::cout.imbue(std::locale());
  std::cout << u8"测试" << std::endl;
  std::ofstream outfile;
  outfile.open("output.txt", std::ios::out);
  outfile << *array[0];
  outfile.close();

  for(int i = 0; i < n_instance; ++i){
    delete array[i];
  }
  delete[] array;
  #endif
  return 0;
}
