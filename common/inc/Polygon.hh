#ifndef TANK_POLYGON_HH
#define TANK_POLYGON_HH

#include "Position.hpp"
#include <vector>

class Polygon {
public:
  Polygon() = default;
  Polygon(const std::vector<Position> &vertices);

  ~Polygon() = default;
  Polygon(const Polygon &other);
  void operator=(const std::vector<Position> &vertices);

  Position &operator[](int idx);

  virtual bool contains(const Position &point) const {
    /* Not implemented */
    return false;
  };

  bool isConvex() const;
  const std::vector<Position> &getOriginVertices() const;
  const std::vector<Position> &getVertices() const;
  std::vector<Position> &getVertices();
  bool hasFace(const Position &a, const Position &b) const;
  int getVerticeIdx(const Position &vertice) const;
  void setPosition(const Position &position);
  Position getPosition() const;
  unsigned int size() const;

private:
  void computeTranslation();

protected:
  std::vector<Position> vertices;
  std::vector<Position> originVertices;
  Position position;
  sf::Vector2f translation;
};

inline std::ostream &operator<<(std::ostream &stream, const Polygon &polygon) {
  const auto &vertices = polygon.getVertices();

  for (const auto &v : vertices) {
    stream << v << std::endl;
  }
  return stream;
}

#endif /* end of include guard: TANK_POLYGON_HH */
