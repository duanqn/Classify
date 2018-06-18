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
#ifdef MULTI
#include <thread>
#endif

//#define DEBUG 1
#ifdef time
#include <ctime>
#endif



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
    array[i] = new Solution(INIT_TEMP, TEMP_DROP_RATE, STOP_TEMP, numStudents*numStudents / 3);
    array[i]->init(numClasses);
  }
  
  Student::s_numSubject = numSubjects;
  Student *s;
  for(int i = 0; i < numStudents; ++i){
    s = new Student();
    datafile >> *s;
    for(int j = 0; j < n_instance; ++j){
      array[j]->addStudent(s);
    }
    //std::cout << *s;
  }
  datafile.close();

  double minEntropy = 2147483647;
  int minpos = 0;
  
  #ifdef TIME
  clock_t t = clock();
  printf("Timing...\n");
  #endif  // TIME

  #ifdef MULTI
  std::thread *pool[n_instance];
  for(int i = 0; i < n_instance; ++i){
    array[i]->randomShuffle();
    pool[i] = new std::thread(&Solution::run, array[i]);
  }
  for(int i = 0; i < n_instance; ++i){
    pool[i]->join();
    delete pool[i];
    if(array[i]->getEntropy() < minEntropy){
      minEntropy = array[i]->getEntropy();
      minpos = i;
    }
  }
  #else
  for(int i = 0; i < n_instance; ++i){
    array[i]->randomShuffle();
    array[i]->run();
    if(array[i]->getEntropy() < minEntropy){
      minEntropy = array[i]->getEntropy();
      minpos = i;
    }
  }
  #endif  // MULTI

  #ifdef TIME
  t = clock() - t;
  printf("Running time: %lf seconds\n", ((double)t)/CLOCKS_PER_SEC);
  #endif  // TIME

  std::ofstream outfile;
  outfile.open("output.txt", std::ios::out);
  outfile << *array[minpos];
  outfile.close();

  array[0]->deleteAllStudents();  // Only delete once!
  for(int i = 0; i < n_instance; ++i){
    delete array[i];
  }
  delete[] array;
  #endif  // DEBUG
  return 0;
}
