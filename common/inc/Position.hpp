#ifndef TANK_POSITION_HPP
#define TANK_POSITION_HPP

#include <SFML/Graphics.hpp>

struct Position {
  float x;
  float y;

  Position(float x = 0, float y = 0) : x(x), y(y) {}

  bool operator==(const Position &pos) const {
    return (pos.x == x && pos.y == y);
  }

  Position operator+(const Position &pos) const {
    Position p = *this;

    p += pos;
    return p;
  }
  Position operator-(const Position &pos) const {
    Position p = *this;

    p -= pos;
    return p;
  }
  void operator+=(const Position &pos) {
    this->x += pos.x;
    this->y += pos.y;
  }
  void operator-=(const Position &pos) {
    this->x -= pos.x;
    this->y -= pos.y;
  }
};

#endif /* end of include guard: TANK_POSITION_HPP */
