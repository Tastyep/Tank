#ifndef TANK_MOVABLE_HH
#define TANK_MOVABLE_HH

#include "Entity.hh"
#include "Updatable.hpp"
#include <memory>

class Movable : public Entity, public Updatable {
public:
  Movable(const sf::Sprite &sprite, double maxVelocity = 2);

  ~Movable() = default;
  Movable(const Movable &other) = default;
  Movable(Movable &&other) = default;
  Movable &operator=(const Movable &other) = default;
  Movable &operator=(Movable &&other) = default;

  virtual void update(Grid &grid, std::chrono::nanoseconds time) = 0;
  virtual void impact(std::shared_ptr<Entity> entity) = 0;
  void draw(sf::RenderTarget &renderTarget) const;
  void setDirection(const sf::Vector2f direction);

protected:
  virtual void displace(int side, std::chrono::nanoseconds time, Grid &grid);
  void rotate(double angle, Grid &grid);

protected:
  double maxVelocity;
  double velocity;
  double acceleration;
  sf::Vector2f direction;
};

#endif /* end of include guard: TANK_MOVABLE_HH */
