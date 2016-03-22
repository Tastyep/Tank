#include "Entities/Player.hh"
#include <iostream>

Player::Player(const sf::Sprite &sprite, IActionAnalyzer &actionAnalyzer)
    : Movable(sprite), actionAnalyzer(actionAnalyzer) {}

bool Player::intersect(const Entity &ent) const { return false; }

void Player::update(std::chrono::nanoseconds time) {
  const std::vector<Action> &actions = this->actionAnalyzer.getActions();

  for (const auto &action : actions) {
    std::cout << "Action on: " << (int)action << "\n";
  }
}