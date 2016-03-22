#ifndef TANK_IACTIONANALYZER_HH_
#define TANK_IACTIONANALYZER_HH_

#include "ActionEnum.hpp"
#include <vector>

class IActionAnalyzer {
public:
  virtual ~IActionAnalyzer() = default;
  virtual const std::vector<Action> &getActions() const = 0;
};

#endif /* end of include guard: TANK_IACTIONANALYZER_HH_ */
