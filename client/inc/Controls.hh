#ifndef _CONTROLS_H_
#define _CONTROLS_H_

#include <SFML/Window.hpp>
#include <array>
#include <map>
#include <utility>
#include <vector>

#include "ActionEnum.hpp"

namespace ctrl {
typedef int key;

enum class type { Keyboard = 0, Mouse, MouseWheel, TypeCount };
enum class state { Unset = 0 };
}

inline Action operator++(Action &x) {
  return (x = static_cast<Action>(static_cast<int>(x) + 1));
}

enum class actionType { Default = 0, Toggle };

struct Entry {
  ctrl::key key;
  ctrl::type type;
  Entry(ctrl::key k = sf::Keyboard::Unknown,
        ctrl::type t = ctrl::type::Keyboard)
      : key(k), type(t) {}
  bool operator==(const Entry &e) const {
    return (key == e.key && type == e.type);
  }
  bool operator==(ctrl::state e) const {
    if (e == ctrl::state::Unset)
      return (key == sf::Keyboard::Unknown && type != ctrl::type::MouseWheel);
    return false;
  }
  void operator=(Entry e) {
    key = e.key;
    type = e.type;
  }
  void operator=(ctrl::state e) {
    if (e == ctrl::state::Unset) {
      key = sf::Keyboard::Unknown;
      type = ctrl::type::Keyboard;
    }
  }
  void fill(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed ||
        event.type == sf::Event::KeyReleased) {
      key = event.key.code;
      type = ctrl::type::Keyboard;
    } else if (event.type == sf::Event::MouseButtonPressed ||
               event.type == sf::Event::MouseButtonReleased) {
      key = event.mouseButton.button;
      type = ctrl::type::Mouse;
    } else if (event.type == sf::Event::MouseWheelMoved) {
      key = event.mouseWheel.delta;
      type = ctrl::type::MouseWheel;
    }
  };
};

typedef struct s_action {
  std::string code;
  actionType type;
  bool state;

  s_action(const std::string &c, actionType t = actionType::Default)
      : code(c), type(t), state(false) {}
} t_action;

struct s_mouseEvent {
  sf::Mouse::Button button;
  sf::Vector2i position;

  s_mouseEvent(sf::Mouse::Button b, const sf::Vector2i &p)
      : button(b), position(p) {}
};

class Controls {
public:
  Controls();
  virtual ~Controls();

  bool isPressed(const Entry &entry);
  Action getActionFromKey(const Entry &entry) const;
  Action getActionFromCode(const std::string &code) const;
  bool getActionState(Action act) const;
  Entry getKeyFromCode(const std::string &code) const;
  Entry getKeyFromAction(Action act) const;
  Entry getLastKey(Action act) const;
  bool isKnownKey(const Entry &entry) const;
  std::pair<bool, std::string> getCodeFromKey(const Entry &entry) const;
  std::pair<bool, std::string> getCodeFromAction(Action act) const;
  const std::array<Entry, 5> &getBoundKeys(Action act) const;
  const sf::Vector2i &getClickPosition(sf::Mouse::Button button) const;

  void unbindKey(const Entry &entry);
  void unbindKeyFromAction(const Entry &entry, Action act);
  void bindKeyOnAction(const Entry &entry, Action act);
  void pressKey(const Entry &entry);
  void releaseKey(const Entry &entry);
  void mouseButtonPressed(const sf::Event &event);
  void mouseMoved(const sf::Event &event);

private:
  std::array<std::map<ctrl::key, bool>,
             static_cast<size_t>(ctrl::type::TypeCount)>
      _keyState;
  std::map<Action, std::array<Entry, 5>> _actionKeys;
  std::map<std::string, Entry> _keycode;
  std::vector<t_action> _actions;
  std::array<sf::Vector2i, static_cast<int>(sf::Mouse::ButtonCount)>
      _mousePosition;
};

#endif /* _CONTROLS_H_ */
