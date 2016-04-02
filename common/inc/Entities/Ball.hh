#ifndef TANK_BALL_HH
#define TANK_BALL_HH

#include "Movable.hh"

class Ball : public Movable {
public:
  Ball(const sf::Sprite &sprite);

  ~Ball() = default;
  Ball(const Ball &other) = default;
  Ball(Ball &&other) = default;
  Ball &operator=(const Ball &other) = default;
  Ball &operator=(Ball &&other) = default;

  void update(Grid &grid, std::chrono::nanoseconds time);

private:
  virtual void displace(int side, std::chrono::nanoseconds time, Grid &grid);
};

#endif /* end of include guard: TANK_BALL_HH */
