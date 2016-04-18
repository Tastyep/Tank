#include "Triangulation.hh"

bool Triangulation::isConvex(const Position &a, const Position &b,
                             const Position &c) const {
  float crossp = (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
  return (crossp >= 0 ? true : false);
}

std::pair<bool, Triangle>
Triangulation::getEar(std::vector<Position> &polygon) const {
  int size = polygon.size();
  bool triTest = false;
  Triangle triangle;

  if (size < 3)
    return {false, triangle};
  else if (size == 3) {
    triangle = Triangle(polygon);
    polygon.clear();
    return {true, triangle};
  } else {
    for (int i = 0; i < size; ++i) {
      triTest = false;
      triangle = Triangle({polygon[(i + size - 1) % size], polygon[i],
                           polygon[(i + 1) % size]});
      if (this->isConvex(triangle[0], triangle[1], triangle[2])) {
        for (const Position &point : polygon) {

          if (triangle.isVertice(point))
            continue;
          if (triangle.contains(point)) {
            triTest = true;
            break;
          }
        }
        if (triTest == false) {
          polygon.erase(polygon.begin() + i);
          return {true, triangle};
        }
      }
    }
  }
  return {false, {}};
}