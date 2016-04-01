#ifndef TANK_POSITION_HPP
#define TANK_POSITION_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

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
  void operator+=(const sf::Vector2f &vec) {
    this->x += vec.x;
    this->y += vec.y;
  }
  void operator-=(const Position &pos) {
    this->x -= pos.x;
    this->y -= pos.y;
  }
};

inline std::ostream &operator<<(std::ostream &stream, const Position &pos) {
  stream << "[" << pos.x << "," << pos.y << "]";
  return stream;
}

#endif /* end of include guard: TANK_POSITION_HPP */
