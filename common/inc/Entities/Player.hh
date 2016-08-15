#ifndef TANK_PLAYER_HH
#define TANK_PLAYER_HH

#include "IActionAnalyzer.hpp"
#include "Movable.hh"
#include <cmath>

class Player : public Movable {
private:
  static constexpr double alpha = 5;

public:
  Player(const EntityBody &body, const sf::Sprite &sprite,
         IActionAnalyzer &actionAnalyzer, const EntityBody &ballBody,
         const sf::Sprite &ballSprite);

  ~Player() = default;
  Player(const Player &other) = default;
  Player(Player &&other) = default;
  Player &operator=(const Player &other) = default;
  Player &operator=(Player &&other) = default;

  void update(Grid &grid, std::chrono::nanoseconds);
  void getImpacted(Entity &entity, const intersectionResult &inter);
  void getImpacted(Ball &entity, const intersectionResult &inter);
  void impact(std::shared_ptr<Entity> entity, const intersectionResult &inter);

private:
  void spawnBall(Grid &grid);

private:
  IActionAnalyzer &actionAnalyzer;
  const EntityBody &ballBody;
  const sf::Sprite &ballSprite;
};

#endif /* end of include guard: TANK_PLAYER_HH */
