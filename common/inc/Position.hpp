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

  Position operator+(const sf::Vector2f &vec) const {
    Position p = *this;

    p += vec;
    return p;
  }
  Position operator+(const Position &pos) const {
    Position p = *this;

    p += pos;
    return p;
  }

  sf::Vector2f operator-(const Position &pos) const {
    sf::Vector2f vec;

    vec.x = this->x - pos.x;
    vec.y = this->y - pos.y;
    return vec;
  }

  void operator+=(const sf::Vector2f &vec) {
    this->x += vec.x;
    this->y += vec.y;
  }
  void operator-=(const sf::Vector2f &vec) {
    this->x -= vec.x;
    this->y -= vec.y;
  }
  void operator+=(const Position &pos) {
    this->x += pos.x;
    this->y += pos.y;
  }
};

inline std::ostream &operator<<(std::ostream &stream, const Position &pos) {
  stream << "[" << pos.x << "," << pos.y << "]";
  return stream;
}

#endif /* end of include guard: TANK_POSITION_HPP */
