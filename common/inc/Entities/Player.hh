#ifndef TANK_PLAYER_HH
#define TANK_PLAYER_HH

#include "IActionAnalyzer.hpp"
#include "Movable.hh"

class Player : public Movable {
public:
  Player(const sf::Sprite &sprite, IActionAnalyzer &actionAnalyzer);

  ~Player() = default;
  Player(const Player &other) = default;
  Player(Player &&other) = default;
  Player &operator=(const Player &other) = default;
  Player &operator=(Player &&other) = default;

  bool intersect(const Entity &ent) const;
  void update(std::chrono::nanoseconds);

private:
  IActionAnalyzer &actionAnalyzer;
};

#endif /* end of include guard: TANK_PLAYER_HH */
