#ifndef _STRINGUTILS_H_
#define _STRINGUTILS_H_

#include <string>
#include <vector>

class StringUtils {
public:
  StringUtils() = default;
  ~StringUtils() = default;

  void split(const std::string &s, char delim,
             std::vector<std::string> &elems) const;
  void tokenString(const std::string &cmd,
                   std::vector<std::string> &tokens) const;
};

#endif /* _STRINGUTILS_H_ */
