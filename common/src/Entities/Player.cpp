#include "Entities/Player.hh"
#include <iostream>

Player::Player(const sf::Sprite &sprite, IActionAnalyzer &actionAnalyzer)
    : Movable(sprite), actionAnalyzer(actionAnalyzer) {
  this->direction.x = std::cos(this->angle * radianConvert);
  this->direction.y = std::sin(this->angle * radianConvert);
}

void Player::update(Grid &grid, std::chrono::nanoseconds time) {
  const std::vector<Action> &actions = this->actionAnalyzer.getActions();

  for (Action act : actions) {
    switch (act) {
    case Action::Left:
    case Action::Right:
      this->rotate((act == Action::Right ? Player::alpha : -Player::alpha),
                   grid);
      break;
    case Action::Forward:
    case Action::Back:
      this->displace((act == Action::Forward ? -1 : 1), time, grid);
      break;
    default:
      break;
    }
  }
}