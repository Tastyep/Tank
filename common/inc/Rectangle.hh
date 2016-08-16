#ifndef TANK_RECTANGLE_HH
#define TANK_RECTANGLE_HH

#include "Polygon.hh"
#include <SFML/Graphics.hpp>
#include <cmath>

class Rectangle : public Polygon {
public:
  Rectangle() = default;
  Rectangle(const Position &tl, const Position &br);

  ~Rectangle() = default;
  Rectangle(const Rectangle &other) = default;
  Rectangle(Rectangle &&other) = default;
  Rectangle &operator=(const Rectangle &other) {
    Polygon::operator=(other);
    this->width = other.width;
    this->height = other.height;
    return *this;
  };
  Rectangle &operator=(Rectangle &&other) {
    Polygon::operator=(other);
    this->width = other.width;
    this->height = other.height;
    return *this;
  };

  float getWidth() const;
  float getHeight() const;

private:
  float width;
  float height;
};

#endif /* end of include guard: TANK_RECTANGLE_HH */
