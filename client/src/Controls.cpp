#include "Controls.hh"
#include <algorithm>

Controls::Controls() {
  using namespace sf;

  _keycode["A"] = Entry(Keyboard::A);
  _keycode["B"] = Entry(Keyboard::B);
  _keycode["C"] = Entry(Keyboard::C);
  _keycode["D"] = Entry(Keyboard::D);
  _keycode["E"] = Entry(Keyboard::E);
  _keycode["F"] = Entry(Keyboard::F);
  _keycode["G"] = Entry(Keyboard::G);
  _keycode["H"] = Entry(Keyboard::H);
  _keycode["I"] = Entry(Keyboard::I);
  _keycode["J"] = Entry(Keyboard::J);
  _keycode["K"] = Entry(Keyboard::K);
  _keycode["L"] = Entry(Keyboard::L);
  _keycode["M"] = Entry(Keyboard::M);
  _keycode["N"] = Entry(Keyboard::N);
  _keycode["O"] = Entry(Keyboard::O);
  _keycode["P"] = Entry(Keyboard::P);
  _keycode["Q"] = Entry(Keyboard::Q);
  _keycode["R"] = Entry(Keyboard::R);
  _keycode["S"] = Entry(Keyboard::S);
  _keycode["T"] = Entry(Keyboard::T);
  _keycode["U"] = Entry(Keyboard::U);
  _keycode["V"] = Entry(Keyboard::V);
  _keycode["W"] = Entry(Keyboard::W);
  _keycode["X"] = Entry(Keyboard::X);
  _keycode["Y"] = Entry(Keyboard::Y);
  _keycode["Z"] = Entry(Keyboard::Z);
  _keycode["NUM0"] = Entry(Keyboard::Num0);
  _keycode["NUM1"] = Entry(Keyboard::Num1);
  _keycode["NUM2"] = Entry(Keyboard::Num2);
  _keycode["NUM3"] = Entry(Keyboard::Num3);
  _keycode["NUM4"] = Entry(Keyboard::Num4);
  _keycode["NUM5"] = Entry(Keyboard::Num5);
  _keycode["NUM6"] = Entry(Keyboard::Num6);
  _keycode["NUM7"] = Entry(Keyboard::Num7);
  _keycode["NUM8"] = Entry(Keyboard::Num8);
  _keycode["NUM9"] = Entry(Keyboard::Num9);
  _keycode["ESCAPE"] = Entry(Keyboard::Escape);
  _keycode["L_CTRL"] = Entry(Keyboard::LControl);
  _keycode["L_SHIFT"] = Entry(Keyboard::LShift);
  _keycode["L_ALT"] = Entry(Keyboard::LAlt);
  _keycode["L_SYSTEM"] = Entry(Keyboard::LSystem);
  _keycode["R_CTRL"] = Entry(Keyboard::RControl);
  _keycode["R_SHIFT"] = Entry(Keyboard::RShift);
  _keycode["R_ALT"] = Entry(Keyboard::RAlt);
  _keycode["R_SYSTEM"] = Entry(Keyboard::RSystem);
  _keycode["MENU"] = Entry(Keyboard::Menu);
  _keycode["LBRACKET"] = Entry(Keyboard::LBracket);
  _keycode["RBRACKET"] = Entry(Keyboard::RBracket);
  _keycode["SEMICOLON"] = Entry(Keyboard::SemiColon);
  _keycode["COMMA"] = Entry(Keyboard::Comma);
  _keycode["PERIOD"] = Entry(Keyboard::Period);
  _keycode["SLASH"] = Entry(Keyboard::Slash);
  _keycode["BACKSLASH"] = Entry(Keyboard::BackSlash);
  _keycode["Tilde"] = Entry(Keyboard::Tilde);
  _keycode["EQUAL"] = Entry(Keyboard::Equal);
  _keycode["DASH"] = Entry(Keyboard::Dash);
  _keycode["SPACE"] = Entry(Keyboard::Space);
  _keycode["ENTER"] = Entry(Keyboard::Return);
  _keycode["BACKSPACE"] = Entry(Keyboard::BackSpace);
  _keycode["TAB"] = Entry(Keyboard::Tab);
  _keycode["PGUP"] = Entry(Keyboard::PageUp);
  _keycode["PGDN"] = Entry(Keyboard::PageDown);
  _keycode["HOME"] = Entry(Keyboard::Home);
  _keycode["INS"] = Entry(Keyboard::Insert);
  _keycode["DEL"] = Entry(Keyboard::Delete);
  _keycode["PLUS"] = Entry(Keyboard::Add);
  _keycode["MINUS"] = Entry(Keyboard::Subtract);
  _keycode["MULT"] = Entry(Keyboard::Multiply);
  _keycode["DIV"] = Entry(Keyboard::Divide);
  _keycode["LEFTARROW"] = Entry(Keyboard::Left);
  _keycode["RIGHTARROW"] = Entry(Keyboard::Right);
  _keycode["UPARROW"] = Entry(Keyboard::Up);
  _keycode["DOWNARROW"] = Entry(Keyboard::Down);
  _keycode["KP_0"] = Entry(Keyboard::Numpad0);
  _keycode["KP_1"] = Entry(Keyboard::Numpad1);
  _keycode["KP_2"] = Entry(Keyboard::Numpad2);
  _keycode["KP_3"] = Entry(Keyboard::Numpad3);
  _keycode["KP_4"] = Entry(Keyboard::Numpad4);
  _keycode["KP_5"] = Entry(Keyboard::Numpad5);
  _keycode["KP_6"] = Entry(Keyboard::Numpad6);
  _keycode["KP_7"] = Entry(Keyboard::Numpad7);
  _keycode["KP_8"] = Entry(Keyboard::Numpad8);
  _keycode["KP_9"] = Entry(Keyboard::Numpad9);
  _keycode["F1"] = Entry(Keyboard::F1);
  _keycode["F2"] = Entry(Keyboard::F2);
  _keycode["F3"] = Entry(Keyboard::F3);
  _keycode["F4"] = Entry(Keyboard::F4);
  _keycode["F5"] = Entry(Keyboard::F5);
  _keycode["F6"] = Entry(Keyboard::F6);
  _keycode["F7"] = Entry(Keyboard::F7);
  _keycode["F8"] = Entry(Keyboard::F8);
  _keycode["F9"] = Entry(Keyboard::F9);
  _keycode["F10"] = Entry(Keyboard::F10);
  _keycode["F11"] = Entry(Keyboard::F11);
  _keycode["F12"] = Entry(Keyboard::F12);
  _keycode["F13"] = Entry(Keyboard::F13);
  _keycode["F14"] = Entry(Keyboard::F14);
  _keycode["F15"] = Entry(Keyboard::F15);
  _keycode["PAUSE"] = Entry(Keyboard::Pause);

  _keycode["MOUSEL"] = Entry(Mouse::Left, ctrl::type::Mouse);
  _keycode["MOUSER"] = Entry(Mouse::Right, ctrl::type::Mouse);
  _keycode["MOUSEM"] = Entry(Mouse::Middle, ctrl::type::Mouse);
  _keycode["MOUSE4"] = Entry(Mouse::XButton1, ctrl::type::Mouse);
  _keycode["MOUSE5"] = Entry(Mouse::XButton2, ctrl::type::Mouse);
  _keycode["MWHEELUP"] = Entry(1, ctrl::type::MouseWheel);
  _keycode["MWHEELDOWN"] = Entry(-1, ctrl::type::MouseWheel);

  _actions.push_back(t_action("forward"));
  _actions.push_back(t_action("back"));
  _actions.push_back(t_action("right"));
  _actions.push_back(t_action("left"));
  _actions.push_back(t_action("use"));
  _actions.push_back(t_action("moveup"));
  _actions.push_back(t_action("movedown"));
  _actions.push_back(t_action("console", actionType::Toggle));
  _actions.push_back(t_action("quickMenu", actionType::Toggle));
  _actions.push_back(t_action("chat", actionType::Toggle));

  for (unsigned int i = 0; i < static_cast<int>(Action::Last); ++i)
    _actionKeys.insert(std::pair<Action, std::array<Entry, 5>>(
        static_cast<Action>(i),
        {Entry(sf::Keyboard::Unknown), Entry(sf::Keyboard::Unknown),
         Entry(sf::Keyboard::Unknown), Entry(sf::Keyboard::Unknown),
         Entry(sf::Keyboard::Unknown)}));
}

Controls::~Controls() {}

bool Controls::isPressed(const Entry &entry) {
  return _keyState[static_cast<int>(entry.type)][entry.key];
}

Action Controls::getActionFromKey(const Entry &entry) const {
  if (entry == ctrl::state::Unset)
    return Action::Unknown;
  for (auto &it : _actionKeys) {
    for (auto &elem : it.second)
      if (elem == entry)
        return it.first;
  }
  return Action::Unknown;
}

Action Controls::getActionFromCode(const std::string &code) const {
  auto it =
      std::find_if(_actions.begin(), _actions.end(),
                   [&code](const t_action &act) { return (act.code == code); });

  return ((it == _actions.end())
              ? Action::Unknown
              : static_cast<Action>(std::distance(_actions.begin(), it)));
}

std::pair<bool, std::string> Controls::getCodeFromAction(Action act) const {
  if (static_cast<int>(act) < 0 ||
      static_cast<unsigned int>(act) >= _actions.size())
    return {false, "No such action"};
  return {true, _actions[static_cast<unsigned int>(act)].code};
}

bool Controls::getActionState(Action act) const {
  return (_actions[static_cast<unsigned int>(act)].state);
}

Entry Controls::getKeyFromCode(const std::string &code) const {
  auto it = _keycode.find(code);

  return ((it == _keycode.end()) ? Entry(sf::Keyboard::Unknown) : it->second);
}

Entry Controls::getKeyFromAction(Action act) const {
  for (auto &it : _actionKeys) {
    if (it.first == act)
      return it.second[0];
  }
  return Entry(sf::Keyboard::Unknown);
}

Entry Controls::getLastKey(Action act) const {
  auto it = _actionKeys.find(act);
  Entry last = Entry(sf::Keyboard::Unknown);

  if (it == _actionKeys.end())
    return last;
  for (auto ait = it->second.begin(); ait != it->second.end(); ++ait) {
    if (*ait == ctrl::state::Unset)
      return last;
    last = *ait;
  }
  return last;
}

bool Controls::isKnownKey(const Entry &entry) const {
  for (auto &it : _keycode)
    if (it.second == entry)
      return true;
  return false;
}

std::pair<bool, std::string>
Controls::getCodeFromKey(const Entry &entry) const {
  for (auto &it : _keycode) {
    if (it.second == entry)
      return {true, it.first};
  }
  return {false, "Key not bound"};
}

const std::array<Entry, 5> &Controls::getBoundKeys(Action act) const {
  auto it = _actionKeys.find(act);

  return it->second;
}

void Controls::unbindKey(const Entry &entry) {
  Action act;

  while ((act = getActionFromKey(entry)) != Action::Unknown)
    unbindKeyFromAction(entry, act);
}

void Controls::unbindKeyFromAction(const Entry &entry, Action act) {
  auto it = _actionKeys.find(act);
  unsigned int i;

  if (it == _actionKeys.end())
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
  auto it = _actionKeys.find(act);

  unbindKey(entry);
  if (it == _actionKeys.end()) {
    _actionKeys.insert(std::pair<Action, std::array<Entry, 5>>(
        act, {Entry(sf::Keyboard::Unknown), Entry(sf::Keyboard::Unknown),
              Entry(sf::Keyboard::Unknown), Entry(sf::Keyboard::Unknown),
              Entry(sf::Keyboard::Unknown)}));
    _actionKeys[act].front() = entry;
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

  _keyState[static_cast<int>(entry.type)][entry.key] = true;
  act = getActionFromKey(entry);
  if (static_cast<int>(act) < 0 ||
      static_cast<unsigned int>(act) >= _actions.size())
    return;
  t_action &action = _actions[static_cast<unsigned int>(act)];
  if (action.type == actionType::Toggle)
    action.state = !action.state;
  else
    action.state = true;
}

void Controls::releaseKey(const Entry &entry) {
  Action act;

  _keyState[static_cast<int>(entry.type)][entry.key] = false;
  act = getActionFromKey(entry);
  if (static_cast<int>(act) < 0 ||
      static_cast<unsigned int>(act) >= _actions.size())
    return;

  t_action &action = _actions[static_cast<unsigned int>(act)];
  if (action.type != actionType::Toggle)
    action.state = false;
}

void Controls::mouseButtonPressed(const sf::Event &event) {
  sf::Vector2i &pos =
      _mousePosition[static_cast<int>(event.mouseButton.button)];

  pos.x = event.mouseButton.x;
  pos.y = event.mouseButton.y;
}

void Controls::mouseMoved(const sf::Event &event) {
  std::map<ctrl::key, bool> &mouseButtons =
      _keyState[static_cast<int>(ctrl::type::Mouse)];
  unsigned int i = 0;

  for (auto &pair : mouseButtons) {
    if (pair.second == true) {
      sf::Vector2i &pos = _mousePosition[i];

      pos.x = event.mouseMove.x;
      pos.y = event.mouseMove.y;
    }
    ++i;
  }
}

const sf::Vector2i &Controls::getClickPosition(sf::Mouse::Button button) const {
  return _mousePosition[static_cast<int>(button)];
}
