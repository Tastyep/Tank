#include "Controls.hh"
#include <algorithm>

Controls::Controls() {
  using namespace sf;

  this->keycode["A"] = Entry(Keyboard::A);
  this->keycode["B"] = Entry(Keyboard::B);
  this->keycode["C"] = Entry(Keyboard::C);
  this->keycode["D"] = Entry(Keyboard::D);
  this->keycode["E"] = Entry(Keyboard::E);
  this->keycode["F"] = Entry(Keyboard::F);
  this->keycode["G"] = Entry(Keyboard::G);
  this->keycode["H"] = Entry(Keyboard::H);
  this->keycode["I"] = Entry(Keyboard::I);
  this->keycode["J"] = Entry(Keyboard::J);
  this->keycode["K"] = Entry(Keyboard::K);
  this->keycode["L"] = Entry(Keyboard::L);
  this->keycode["M"] = Entry(Keyboard::M);
  this->keycode["N"] = Entry(Keyboard::N);
  this->keycode["O"] = Entry(Keyboard::O);
  this->keycode["P"] = Entry(Keyboard::P);
  this->keycode["Q"] = Entry(Keyboard::Q);
  this->keycode["R"] = Entry(Keyboard::R);
  this->keycode["S"] = Entry(Keyboard::S);
  this->keycode["T"] = Entry(Keyboard::T);
  this->keycode["U"] = Entry(Keyboard::U);
  this->keycode["V"] = Entry(Keyboard::V);
  this->keycode["W"] = Entry(Keyboard::W);
  this->keycode["X"] = Entry(Keyboard::X);
  this->keycode["Y"] = Entry(Keyboard::Y);
  this->keycode["Z"] = Entry(Keyboard::Z);
  this->keycode["NUM0"] = Entry(Keyboard::Num0);
  this->keycode["NUM1"] = Entry(Keyboard::Num1);
  this->keycode["NUM2"] = Entry(Keyboard::Num2);
  this->keycode["NUM3"] = Entry(Keyboard::Num3);
  this->keycode["NUM4"] = Entry(Keyboard::Num4);
  this->keycode["NUM5"] = Entry(Keyboard::Num5);
  this->keycode["NUM6"] = Entry(Keyboard::Num6);
  this->keycode["NUM7"] = Entry(Keyboard::Num7);
  this->keycode["NUM8"] = Entry(Keyboard::Num8);
  this->keycode["NUM9"] = Entry(Keyboard::Num9);
  this->keycode["ESCAPE"] = Entry(Keyboard::Escape);
  this->keycode["L_CTRL"] = Entry(Keyboard::LControl);
  this->keycode["L_SHIFT"] = Entry(Keyboard::LShift);
  this->keycode["L_ALT"] = Entry(Keyboard::LAlt);
  this->keycode["L_SYSTEM"] = Entry(Keyboard::LSystem);
  this->keycode["R_CTRL"] = Entry(Keyboard::RControl);
  this->keycode["R_SHIFT"] = Entry(Keyboard::RShift);
  this->keycode["R_ALT"] = Entry(Keyboard::RAlt);
  this->keycode["R_SYSTEM"] = Entry(Keyboard::RSystem);
  this->keycode["MENU"] = Entry(Keyboard::Menu);
  this->keycode["LBRACKET"] = Entry(Keyboard::LBracket);
  this->keycode["RBRACKET"] = Entry(Keyboard::RBracket);
  this->keycode["SEMICOLON"] = Entry(Keyboard::SemiColon);
  this->keycode["COMMA"] = Entry(Keyboard::Comma);
  this->keycode["PERIOD"] = Entry(Keyboard::Period);
  this->keycode["SLASH"] = Entry(Keyboard::Slash);
  this->keycode["BACKSLASH"] = Entry(Keyboard::BackSlash);
  this->keycode["Tilde"] = Entry(Keyboard::Tilde);
  this->keycode["EQUAL"] = Entry(Keyboard::Equal);
  this->keycode["DASH"] = Entry(Keyboard::Dash);
  this->keycode["SPACE"] = Entry(Keyboard::Space);
  this->keycode["ENTER"] = Entry(Keyboard::Return);
  this->keycode["BACKSPACE"] = Entry(Keyboard::BackSpace);
  this->keycode["TAB"] = Entry(Keyboard::Tab);
  this->keycode["PGUP"] = Entry(Keyboard::PageUp);
  this->keycode["PGDN"] = Entry(Keyboard::PageDown);
  this->keycode["HOME"] = Entry(Keyboard::Home);
  this->keycode["INS"] = Entry(Keyboard::Insert);
  this->keycode["DEL"] = Entry(Keyboard::Delete);
  this->keycode["PLUS"] = Entry(Keyboard::Add);
  this->keycode["MINUS"] = Entry(Keyboard::Subtract);
  this->keycode["MULT"] = Entry(Keyboard::Multiply);
  this->keycode["DIV"] = Entry(Keyboard::Divide);
  this->keycode["LEFTARROW"] = Entry(Keyboard::Left);
  this->keycode["RIGHTARROW"] = Entry(Keyboard::Right);
  this->keycode["UPARROW"] = Entry(Keyboard::Up);
  this->keycode["DOWNARROW"] = Entry(Keyboard::Down);
  this->keycode["KP_0"] = Entry(Keyboard::Numpad0);
  this->keycode["KP_1"] = Entry(Keyboard::Numpad1);
  this->keycode["KP_2"] = Entry(Keyboard::Numpad2);
  this->keycode["KP_3"] = Entry(Keyboard::Numpad3);
  this->keycode["KP_4"] = Entry(Keyboard::Numpad4);
  this->keycode["KP_5"] = Entry(Keyboard::Numpad5);
  this->keycode["KP_6"] = Entry(Keyboard::Numpad6);
  this->keycode["KP_7"] = Entry(Keyboard::Numpad7);
  this->keycode["KP_8"] = Entry(Keyboard::Numpad8);
  this->keycode["KP_9"] = Entry(Keyboard::Numpad9);
  this->keycode["F1"] = Entry(Keyboard::F1);
  this->keycode["F2"] = Entry(Keyboard::F2);
  this->keycode["F3"] = Entry(Keyboard::F3);
  this->keycode["F4"] = Entry(Keyboard::F4);
  this->keycode["F5"] = Entry(Keyboard::F5);
  this->keycode["F6"] = Entry(Keyboard::F6);
  this->keycode["F7"] = Entry(Keyboard::F7);
  this->keycode["F8"] = Entry(Keyboard::F8);
  this->keycode["F9"] = Entry(Keyboard::F9);
  this->keycode["F10"] = Entry(Keyboard::F10);
  this->keycode["F11"] = Entry(Keyboard::F11);
  this->keycode["F12"] = Entry(Keyboard::F12);
  this->keycode["F13"] = Entry(Keyboard::F13);
  this->keycode["F14"] = Entry(Keyboard::F14);
  this->keycode["F15"] = Entry(Keyboard::F15);
  this->keycode["PAUSE"] = Entry(Keyboard::Pause);

  this->keycode["MOUSEL"] = Entry(Mouse::Left, ctrl::type::Mouse);
  this->keycode["MOUSER"] = Entry(Mouse::Right, ctrl::type::Mouse);
  this->keycode["MOUSEM"] = Entry(Mouse::Middle, ctrl::type::Mouse);
  this->keycode["MOUSE4"] = Entry(Mouse::XButton1, ctrl::type::Mouse);
  this->keycode["MOUSE5"] = Entry(Mouse::XButton2, ctrl::type::Mouse);
  this->keycode["MWHEELUP"] = Entry(1, ctrl::type::MouseWheel);
  this->keycode["MWHEELDOWN"] = Entry(-1, ctrl::type::MouseWheel);

  this->actions.push_back(t_action("forward"));
  this->actions.push_back(t_action("back"));
  this->actions.push_back(t_action("right"));
  this->actions.push_back(t_action("left"));
  this->actions.push_back(t_action("use"));
  this->actions.push_back(t_action("moveup"));
  this->actions.push_back(t_action("movedown"));
  this->actions.push_back(t_action("console", actionType::Toggle));
  this->actions.push_back(t_action("quickMenu", actionType::Toggle));
  this->actions.push_back(t_action("chat", actionType::Toggle));

  for (unsigned int i = 0; i < static_cast<int>(Action::Last); ++i)
    this->actionKeys.insert(std::pair<Action, std::array<Entry, 5>>(
        static_cast<Action>(i),
        {Entry(sf::Keyboard::Unknown), Entry(sf::Keyboard::Unknown),
         Entry(sf::Keyboard::Unknown), Entry(sf::Keyboard::Unknown),
         Entry(sf::Keyboard::Unknown)}));
}

Controls::~Controls() {}

bool Controls::isPressed(const Entry &entry) {
  return this->keyState[static_cast<int>(entry.type)][entry.key];
}

Action Controls::getActionFromKey(const Entry &entry) const {
  if (entry == ctrl::state::Unset)
    return Action::Unknown;
  for (auto &it : this->actionKeys) {
    for (auto &elem : it.second)
      if (elem == entry)
        return it.first;
  }
  return Action::Unknown;
}

Action Controls::getActionFromCode(const std::string &code) const {
  auto it =
      std::find_if(this->actions.begin(), this->actions.end(),
                   [&code](const t_action &act) { return (act.code == code); });

  return ((it == this->actions.end())
              ? Action::Unknown
              : static_cast<Action>(std::distance(this->actions.begin(), it)));
}

std::pair<bool, std::string> Controls::getCodeFromAction(Action act) const {
  if (static_cast<int>(act) < 0 ||
      static_cast<unsigned int>(act) >= this->actions.size())
    return {false, "No such action"};
  return {true, this->actions[static_cast<unsigned int>(act)].code};
}

bool Controls::getActionState(Action act) const {
  return (this->actions[static_cast<unsigned int>(act)].state);
}

Entry Controls::getKeyFromCode(const std::string &code) const {
  auto it = this->keycode.find(code);

  return ((it == this->keycode.end()) ? Entry(sf::Keyboard::Unknown)
                                      : it->second);
}

Entry Controls::getKeyFromAction(Action act) const {
  for (auto &it : this->actionKeys) {
    if (it.first == act)
      return it.second[0];
  }
  return Entry(sf::Keyboard::Unknown);
}

Entry Controls::getLastKey(Action act) const {
  auto it = this->actionKeys.find(act);
  Entry last = Entry(sf::Keyboard::Unknown);

  if (it == this->actionKeys.end())
    return last;
  for (auto ait = it->second.begin(); ait != it->second.end(); ++ait) {
    if (*ait == ctrl::state::Unset)
      return last;
    last = *ait;
  }
  return last;
}

bool Controls::isKnownKey(const Entry &entry) const {
  for (auto &it : this->keycode)
    if (it.second == entry)
      return true;
  return false;
}

std::pair<bool, std::string>
Controls::getCodeFromKey(const Entry &entry) const {
  for (auto &it : this->keycode) {
    if (it.second == entry)
      return {true, it.first};
  }
  return {false, "Key not bound"};
}

const std::array<Entry, 5> &Controls::getBoundKeys(Action act) const {
  auto it = this->actionKeys.find(act);

  return it->second;
}

void Controls::unbindKey(const Entry &entry) {
  Action act;

  while ((act = getActionFromKey(entry)) != Action::Unknown)
    unbindKeyFromAction(entry, act);
}

void Controls::unbindKeyFromAction(const Entry &entry, Action act) {
  auto it = this->actionKeys.find(act);
  unsigned int i;

  if (it == this->actionKeys.end())
    return;

  std::array<Entry, 5> &keys = it->second;
  for (i = 0; i < keys.size(); ++i)
    if (entry == keys[i])
      break;
  while (i < keys.size() - 1) {
    keys[i] = keys[i + 1];
    ++i;
  }
  while (i < keys.size()) {
    keys[i] = ctrl::state::Unset;
    ++i;
  }
}

void Controls::bindKeyOnAction(const Entry &entry, Action act) {
  auto it = this->actionKeys.find(act);

  unbindKey(entry);
  if (it == this->actionKeys.end()) {
    this->actionKeys.insert(std::pair<Action, std::array<Entry, 5>>(
        act, {Entry(sf::Keyboard::Unknown), Entry(sf::Keyboard::Unknown),
              Entry(sf::Keyboard::Unknown), Entry(sf::Keyboard::Unknown),
              Entry(sf::Keyboard::Unknown)}));
    this->actionKeys[act].front() = entry;
    return;
  }

  std::array<Entry, 5> &keys = it->second;
  for (auto &entryKey : keys)
    if (entryKey == ctrl::state::Unset) {
      entryKey = entry;
      return;
    }
  for (unsigned int i = 0; i < keys.size() - 1; ++i)
    keys[i] = keys[i + 1];
  keys.back() = entry;
}

void Controls::pressKey(const Entry &entry) {
  Action act;

  this->keyState[static_cast<int>(entry.type)][entry.key] = true;
  act = getActionFromKey(entry);
  if (static_cast<int>(act) < 0 ||
      static_cast<unsigned int>(act) >= this->actions.size())
    return;
  t_action &action = this->actions[static_cast<unsigned int>(act)];
  if (action.type == actionType::Toggle)
    action.state = !action.state;
  else
    action.state = true;
}

void Controls::releaseKey(const Entry &entry) {
  Action act;

  this->keyState[static_cast<int>(entry.type)][entry.key] = false;
  act = getActionFromKey(entry);
  if (static_cast<int>(act) < 0 ||
      static_cast<unsigned int>(act) >= this->actions.size())
    return;

  t_action &action = this->actions[static_cast<unsigned int>(act)];
  if (action.type != actionType::Toggle)
    action.state = false;
}

void Controls::mouseButtonPressed(const sf::Event &event) {
  sf::Vector2i &pos =
      this->mousePosition[static_cast<int>(event.mouseButton.button)];

  pos.x = event.mouseButton.x;
  pos.y = event.mouseButton.y;
}

void Controls::mouseMoved(const sf::Event &event) {
  std::map<ctrl::key, bool> &mouseButtons =
      this->keyState[static_cast<int>(ctrl::type::Mouse)];
  unsigned int i = 0;

  for (auto &pair : mouseButtons) {
    if (pair.second == true) {
      sf::Vector2i &pos = this->mousePosition[i];

      pos.x = event.mouseMove.x;
      pos.y = event.mouseMove.y;
    }
    ++i;
  }
}

const sf::Vector2i &Controls::getClickPosition(sf::Mouse::Button button) const {
  return this->mousePosition[static_cast<int>(button)];
}
