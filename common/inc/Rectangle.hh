#ifndef TANK_RECTANGLE_HH
#define TANK_RECTANGLE_HH

#include "Position.hpp"
#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>

#include <iostream>

class Rectangle {
private:
  static constexpr auto pi = std::acos(-1);
  static constexpr double radianConvert = (pi / 180.0);

public:
  Rectangle() = default;
  Rectangle(const Position &tl, const Position &br);

  ~Rectangle() = default;
  Rectangle(const Rectangle &other) = default;
  Rectangle(Rectangle &&other) = default;
  Rectangle &operator=(const Rectangle &other) {
    this->edges = other.edges;
    this->width = other.width;
    this->height = other.height;
    this->translation = other.translation;
    return *this;
  };
  Rectangle &operator=(Rectangle &&other) {
    this->edges = other.edges;
    this->width = other.width;
    this->height = other.height;
    this->translation = other.translation;
    return *this;
  };

  void setPosition(const Position &pos);
  void move(const sf::Vector2f &displacement);
  void rotate(double angle);
  const std::array<Position, 4> &getEdges() const;
  bool intersects(const Rectangle &rect) const;
  void setInternTranslation(const sf::Vector2f &tr);
  float getWidth() const;
  float getHeight() const;

private:
  std::array<Position, 4> edges;
  float width;
  float height;
  sf::Vector2f translation;
};

#endif /* end of include guard: TANK_RECTANGLE_HH */
