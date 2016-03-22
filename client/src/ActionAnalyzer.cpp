#include "ActionAnalyzer.hh"

ActionAnalyzer::ActionAnalyzer()
    : oldActionState(static_cast<int>(Action::Last), false),
      diffState(static_cast<int>(Action::Last), -1) {}

ActionAnalyzer::~ActionAnalyzer() {}

unsigned int ActionAnalyzer::computeInputChanges(Settings &set) {
  Controls &ctrl = set.getControls();
  bool cuState;
  int idx;
  unsigned int changes = 0;

  this->actions.clear();
  std::fill(this->diffState.begin(), this->diffState.end(), -1);
  for (Action act = Action::Forward; act < Action::Last; ++act) {
    cuState = ctrl.getActionState(act);
    idx = static_cast<int>(act);
    if (cuState != this->oldActionState[idx]) {
      this->oldActionState[idx] = cuState;
      this->diffState[idx] = cuState;
      ++changes;
    }
    if (cuState == true)
      this->actions.push_back(act);
  }
  return changes;
}

const std::vector<Action> &ActionAnalyzer::getActions() const {
  return this->actions;
}

const std::vector<char> &ActionAnalyzer::getChanges() const {
  return this->diffState;
}

std::string ActionAnalyzer::serialize() {
  // ClientMessage msg;
  // ClientActions *actions = new ClientActions;
  // ClientAction *action;
  std::string serialized;
  // unsigned int actionId = -1;
  //
  // for (auto state : this->diffState) {
  //   ++actionId;
  //   if (state == -1)
  //     continue;
  //   action = actions->add_actions();
  //   if (action == nullptr)
  //     continue;
  //   action->set_name(actionId);
  //   action->set_state(static_cast<bool>(state));
  // }
  // msg.set_content(ClientMessage::ACTION);
  // msg.set_allocated_actions(actions);
  // msg.SerializeToString(&serialized);
  return serialized;
}
