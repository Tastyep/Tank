#ifndef TANK_POLYGON_HH
#define TANK_POLYGON_HH

#include "Position.hpp"
#include <vector>

class Polygon {
public:
  Polygon() = default;
  Polygon(const std::vector<Position> &vertices);

  ~Polygon() = default;
  Polygon(const Polygon &other) { this->vertices = other.vertices; };
  void operator<<(const std::vector<Position> &vertices) {
    this->vertices = vertices;
  };

  Position &operator[](int idx);

  virtual bool contains(const Position &point) const {
    /* Not implemented */
    return false;
  };

  bool isConvex() const;
  const std::vector<Position> &getVertices() const;
  bool hasFace(const Position &a, const Position &b) const;
  int getVerticeIdx(const Position &vertice) const;
  unsigned int size() const;

protected:
  std::vector<Position> vertices;
};

inline std::ostream &operator<<(std::ostream &stream, const Polygon &polygon) {
  const auto &vertices = polygon.getVertices();

  for (const auto &v : vertices) {
    stream << v << std::endl;
  }
  return stream;
}

#endif /* end of include guard: TANK_POLYGON_HH */
