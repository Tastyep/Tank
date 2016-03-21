#ifndef TANK_POSITION_HPP
#define TANK_POSITION_HPP

struct Position {
  float x;
  float y;

  bool operator==(const Position &pos) const {
    return (pos.x == x && pos.y == y);
  }
};

#endif /* end of include guard: TANK_POSITION_HPP */
