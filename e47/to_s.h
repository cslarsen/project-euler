#include <string>
#include <vector>
#include <set>
#include <sstream>

const char* to_s(const std::string& s)
{
  static char b[1000*1024];
  b[0] = '\0';
  strncpy(b, s.c_str(), sizeof(b));
  return b;
}

const char* to_s(const std::vector<int>& v)
{
  std::stringstream s;

  for ( size_t n=0; n < v.size(); ++n )
    s << v[n] << (n+1 < v.size() ? ", " : "");

  return to_s(s.str());
}

const char* to_s(const std::set<int>& v)
{
  std::stringstream s;

  for ( std::set<int>::iterator i = v.begin(); i != v.end(); ++i )
    s << *i << " ";

  return to_s(s.str());
}
