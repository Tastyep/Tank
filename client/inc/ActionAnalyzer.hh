#ifndef _ACTIONANALYZER_H_
#define _ACTIONANALYZER_H_

//#include "ISerialize.hpp"
#include "IActionAnalyzer.hpp"
#include "Settings.hh"

class ActionAnalyzer : public IActionAnalyzer /*: public ISerialize*/ {
public:
  ActionAnalyzer();
  virtual ~ActionAnalyzer();

  unsigned int computeInputChanges(Settings &set);
  const std::vector<Action> &getActions() const override;
  const std::vector<char> &getChanges() const;
  std::string serialize();

private:
  std::vector<bool> oldActionState;
  std::vector<char> diffState;
  std::vector<Action> actions;
};

#endif /* _ACTIONANALYZER_H_ */
