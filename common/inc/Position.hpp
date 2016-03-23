#ifndef TANK_POSITION_HPP
#define TANK_POSITION_HPP

struct Position {
  float x;
  float y;

  Position(float x = 0, float y = 0) : x(x), y(y) {}
  bool operator==(const Position &pos) const {
    return (pos.x == x && pos.y == y);
  }
};

#endif /* end of include guard: TANK_POSITION_HPP */
