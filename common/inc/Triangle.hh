#ifndef TANK_TRIANGLE_HH
#define TANK_TRIANGLE_HH

#include "Polygon.hh"

class Triangle : public Polygon {
public:
  Triangle() = default;
  Triangle(const std::vector<Position> &vertices);

  ~Triangle() = default;
  Triangle(const Triangle &other) { Polygon::operator=(other); };

  bool contains(const Position &point) const;
  bool isVertice(const Position &point) const;
};

#endif /* end of include guard: TANK_TRIANGLE_HH */
