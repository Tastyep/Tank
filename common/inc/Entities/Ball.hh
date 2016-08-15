#ifndef TANK_BALL_HH
#define TANK_BALL_HH

#include "Movable.hh"

class Wall;

class Ball : public Movable {
public:
  Ball(const EntityBody &body, const sf::Sprite &sprite);

  ~Ball() = default;
  Ball(const Ball &other) = default;
  Ball(Ball &&other) = default;
  Ball &operator=(const Ball &other) = default;
  Ball &operator=(Ball &&other) = default;

  void update(Grid &grid, std::chrono::nanoseconds time);
  void getImpacted(Entity &entity, const intersectionResult &inter);
  void impact(std::shared_ptr<Entity> entity, const intersectionResult &inter);
  void bounce();
  void computeReflectedDirection(const Wall &wall,
                                 const intersectionResult &inter);

private:
  virtual void displace(int side, std::chrono::nanoseconds time, Grid &grid);

private:
  unsigned int bounceCount;
  unsigned int maxBounce;
};

#endif /* end of include guard: TANK_BALL_HH */
