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
  bool hasFace(const Position &a, const Position &b) const;
  int getVerticeIdx(const Position &vertice) const;
  void setPosition(const Position &position);
  void move(const sf::Vector2f &displacement);
  void rotate(double cs, double sn, const Position &rotationCenter);
  const std::vector<sf::Vector2f> &getAxis() const;
  Position getPosition() const;
  unsigned int size() const;

private:
  void computeTranslation();
  void computeAxis();

protected:
  std::vector<Position> vertices;
  std::vector<Position> originVertices;
  std::vector<sf::Vector2f> axis;
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
