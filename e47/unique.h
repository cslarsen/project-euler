#include <set>
#include <vector>

std::vector<int> unique(const std::vector<int>& v)
{
  std::set<int> s;
  for ( std::vector<int>::const_iterator i = v.begin(); i != v.end(); ++i )
    s.insert(*i);

  std::vector<int> r;
  for ( std::set<int>::const_iterator i = s.begin(); i != s.end(); ++i )
    r.push_back(*i);
  
  return r;
}
