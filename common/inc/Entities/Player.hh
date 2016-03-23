#ifndef TANK_PLAYER_HH
#define TANK_PLAYER_HH

#include "IActionAnalyzer.hpp"
#include "Movable.hh"
#include <cmath>

class Player : public Movable {
private:
  static constexpr double alpha = 5;
  static constexpr auto pi = std::acos(-1);
  static constexpr double radianConvert = (pi / 180.0);

public:
  Player(const sf::Sprite &sprite, IActionAnalyzer &actionAnalyzer);

  ~Player() = default;
  Player(const Player &other) = default;
  Player(Player &&other) = default;
  Player &operator=(const Player &other) = default;
  Player &operator=(Player &&other) = default;

  bool intersect(const Entity &ent) const;
  void update(Grid &grid, std::chrono::nanoseconds);

private:
  void rotate(Action act);
  void displace(Action act, std::chrono::nanoseconds time);

private:
  IActionAnalyzer &actionAnalyzer;
  double angle;
};

#endif /* end of include guard: TANK_PLAYER_HH */
