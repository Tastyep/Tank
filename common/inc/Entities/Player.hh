#ifndef TANK_PLAYER_HH
#define TANK_PLAYER_HH

#include "Entity.hpp"

class Player : public Entity {
public:
  Player(const sf::Sprite &sprite);

  ~Player() = default;
  Player(const Player &other) = default;
  Player(Player &&other) = default;
  Player &operator=(const Player &other) = default;
  Player &operator=(Player &&other) = default;

  bool intersect(const Entity &ent) const;
  void draw(sf::RenderTarget &renderTarget) const;
};

#endif /* end of include guard: TANK_PLAYER_HH */
