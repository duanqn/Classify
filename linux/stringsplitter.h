#ifndef STRINGSPLITTER_H_
#define STRINGSPLITTER_H_
// http://stackoverflow.com/a/9379203/106471
#include <iostream>                                                              
#include <iomanip>
#include <string>
#include <sstream>
#include <ctime>
#include <vector>

class StringRef
{
private:
  char const*     begin_;
  int             size_;

public:
  int size() const { return size_; }
  char const* begin() const { return begin_; }
  char const* end() const { return begin_ + size_; }

  StringRef( char const* const begin, int const size )
    : begin_( begin )
    , size_( size )
  {}
};

void split( std::string const& str, std::vector<StringRef> &result, char delimiter = ' ' );
void split( std::string const& str, std::vector<std::string> &result, char delimiter = ' ' );
#endif // STRINGSPLITTER_H_