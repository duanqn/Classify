#include "stringsplitter.h"
#ifdef DEBUG
#include <cstdio>
#endif

void split( std::string const& str, std::vector<StringRef> &result, char delimiter)
{
  enum State { inSpace, inToken };

  State state = inSpace;
  char const*     pTokenBegin = str.c_str();    // Init to satisfy compiler.
  for( auto it = str.begin(); it != str.end(); ++it )
  {
    State const newState = (*it == delimiter? inSpace : inToken);
    if(newState == inSpace){
      #ifdef DEBUG
      printf("Delimiter encountered.\n");
      #endif
      result.push_back( StringRef( pTokenBegin, &*it - pTokenBegin ) );
      if(it+1 != str.end()){
        pTokenBegin = &(*(it+1));
      }
    }
    state = newState;
  }
  if( state == inToken )
  {
    result.push_back( StringRef( pTokenBegin, &*str.end() - pTokenBegin ) );
  }
  #ifdef DEBUG
  printf("Function returns\n");
  #endif
}

void split( std::string const& str, std::vector<std::string> &result, char delimiter){
  std::vector<StringRef> _res;
  split(str, _res, delimiter);
  #ifdef DEBUG
  printf("split() returns\n");
  #endif
  for(auto it = _res.begin(); it != _res.end(); ++it){
    #ifdef DEBUG
    printf("%p to %p\n", it->begin(), it->begin() + it->size());
    #endif
    result.push_back(std::string(it->begin(), it->size()));
  }
  #ifdef DEBUG
  printf("Function returns\n");
  #endif
}
#ifdef DEBUG
#undef DEBUG
#endif
