#ifndef TANK_PLAYER_HH
#define TANK_PLAYER_HH

#include "IActionAnalyzer.hpp"
#include "Movable.hh"
#include <cmath>

class Player : public Movable {
private:
  static constexpr double alpha = 5;

public:
  Player(const sf::Sprite &sprite, IActionAnalyzer &actionAnalyzer);

  ~Player() = default;
  Player(const Player &other) = default;
  Player(Player &&other) = default;
  Player &operator=(const Player &other) = default;
  Player &operator=(Player &&other) = default;

  void update(Grid &grid, std::chrono::nanoseconds);

private:
  IActionAnalyzer &actionAnalyzer;
};

#endif /* end of include guard: TANK_PLAYER_HH */
