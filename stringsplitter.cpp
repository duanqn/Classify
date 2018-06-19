#include "stringsplitter.h"

void split( std::string const& str, std::vector<StringRef> &result, char delimiter)
{
  enum State { inSpace, inToken };

  State state = inSpace;
  char const*     pTokenBegin = 0;    // Init to satisfy compiler.
  for( auto it = str.begin(); it != str.end(); ++it )
  {
    State const newState = (*it == delimiter? inSpace : inToken);
    if( newState != state )
    {
      switch( newState )
      {
      case inSpace:
        result.push_back( StringRef( pTokenBegin, &*it - pTokenBegin ) );
        break;
      case inToken:
        pTokenBegin = &*it;
        break;
      }
    }
    state = newState;
  }
  if( state == inToken )
  {
    result.push_back( StringRef( pTokenBegin, &*str.end() - pTokenBegin ) );
  }
}

void split( std::string const& str, std::vector<std::string> &result, char delimiter){
  std::vector<StringRef> _res;
  split(str, _res, delimiter);
  for(auto it = _res.begin(); it != _res.end(); ++it){
    result.push_back(std::string(it->begin(), it->size()));
  }
}
