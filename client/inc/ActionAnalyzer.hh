#ifndef _ACTIONANALYZER_H_
#define _ACTIONANALYZER_H_

//#include "ISerialize.hpp"
#include "Settings.hh"
#include <vector>

class ActionAnalyzer /*: public ISerialize*/ {
public:
  ActionAnalyzer();
  virtual ~ActionAnalyzer();

  unsigned int computeInputChanges(Settings &set);
  const std::vector<bool> &getInputChanges() const;
  std::string serialize();

private:
  std::vector<bool> oldActionState;
  std::vector<bool> diffState;
};

#endif /* _ACTIONANALYZER_H_ */
