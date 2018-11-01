#include "stringsplitter.h"
#include <vector>
#include <string>
#include <initializer_list>
#include <cstdio>
#include <iostream>

std::vector<std::string> teststr;
std::vector<char> delimiter;
std::vector<std::vector<std::string> > groundtruth;
int main(){
  const char *filename = "stringsplitter.test.txt";
  FILE *fin = fopen(filename, "r");
  char buf[200];
  int segs = 0;
  char delim = '\0';
  while(fgets(buf, 200, fin) != NULL){
    printf("String received: %s\n", buf);
    std::string tmp = std::string(buf);
    tmp = tmp.substr(0, tmp.size() - 1);
    if(tmp.empty()){
      break;
    }
    //printf("After trimming: %s\n", tmp.c_str());
    teststr.push_back(tmp);
    fscanf(fin, "%d %c\n", &segs, &delim);
    delimiter.push_back(delim);
    groundtruth.push_back(std::vector<std::string>());
    for(int i = 0; i < segs; ++i){
      //printf("Seg %d\n", i);
      fgets(buf, 200, fin);
      tmp = std::string(buf);
      tmp = tmp.substr(0, tmp.size() - 1);
      groundtruth[groundtruth.size() - 1].push_back(tmp);
    }
  }
  fclose(fin);

  /*
  for(auto it = groundtruth.begin(); it != groundtruth.end(); ++it){
    std::cout << "===============" << std::endl;
    for(auto jt = it->begin(); jt != it->end(); ++jt){
      std::cout << *jt << std::endl;
    }
    std::cout << std::endl;
  }
  */
  std::vector<StringRef> res;
  for(int i = 0; i < teststr.size(); ++i){
    res.clear();  // MUST
    split(teststr[i], res, delimiter[i]);
    for(int j = 0; j < res.size(); ++j){
      std::string tmp = std::string(res[j].begin(), res[j].size());
      if(tmp != groundtruth[i][j]){
        std::cout << "***Error!***" << std::endl;
        std::cout << "output: \"" << tmp << "\"" << std::endl;
        std::cout << "expected: \"" << groundtruth[i][j] << "\"" << std::endl;
      }
    }
  }
  return 0;
}
