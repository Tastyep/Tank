#ifndef _ACVAR_H_
#define _ACVAR_H_

#include <iostream>
#include <map>
#include <vector>

enum cvarType { Number, String };

/*
** restrictValue content:
** default - {min, max} or {val1, val2, valX}
*/

enum class Restriction { None = 0, Range, Value };

struct Cvar {
  std::vector<std::string> restrictValue;
  std::string defaultValue;
  std::string value;
  cvarType type;
  Restriction restrictType;
  Cvar(const std::vector<std::string> &vec, const std::string &dValue,
       const std::string &val, cvarType dtype,
       Restriction restric = Restriction::Range)
      : restrictValue(vec), defaultValue(dValue), value(val), type(dtype),
        restrictType(restric) {}
};

class ACvar {
public:
  ACvar() = default;
  virtual ~ACvar() = default;

  std::pair<bool, std::string> setCvar(const std::string &name,
                                       const std::string &value);

  bool isCvar(const std::string &name) const;
  const std::vector<std::string> &getCvarInfo(const std::string &name) const;
  const std::string &getCvar(const std::string &name) const;
  bool addCvar(const std::string &name, Cvar *cvar);

protected:
  std::map<std::string, Cvar *> cvars;
};

#endif /* _CVAR_H_ */
