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