#ifndef TANK_MOVABLE_HH
#define TANK_MOVABLE_HH

#include "Entity.hpp"
#include "Updatable.hpp"

class Movable : public Entity, public Updatable {
public:
  Movable(const sf::Sprite &sprite, double maxVelocity = 2);

  ~Movable() = default;
  Movable(const Movable &other) = default;
  Movable(Movable &&other) = default;
  Movable &operator=(const Movable &other) = default;
  Movable &operator=(Movable &&other) = default;

  virtual void update(Grid &grid, std::chrono::nanoseconds time) = 0;
  void draw(sf::RenderTarget &renderTarget) const;
  virtual bool intersect(const Entity &ent) const = 0;

protected:
  double maxVelocity;
  double velocity;
  double acceleration;
  sf::Vector2f direction;
};

#endif /* end of include guard: TANK_MOVABLE_HH */
