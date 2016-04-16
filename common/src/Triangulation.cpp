#include "Triangulation.hh"

bool Triangulation::isConvex(const Position &a, const Position &b,
                             const Position &c) const {
  float crossp = (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
  return (crossp >= 0 ? true : false);
}

bool Triangulation::inTriangle(const Position &a, const Position &b,
                               const Position &c, const Position &x) const {
  std::array<float, 3> barCoef = {0, 0, 0};

  barCoef[0] = ((b.y - c.y) * (x.x - c.x) + (c.x - b.x) * (x.y - c.y)) /
               (((b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y)));
  barCoef[1] = ((c.y - a.y) * (x.x - c.x) + (a.x - c.x) * (x.y - c.y)) /
               (((b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y)));
  barCoef[2] = 1.f - barCoef[0] - barCoef[1];

  for (float coef : barCoef) {
    if (coef >= 1 || coef <= 0)
      return false;
  }
  return true;
}

std::pair<bool, std::array<Position, 3>>
Triangulation::getEar(std::vector<Position> &polygon) const {
  int size = polygon.size();
  bool triTest = false;
  std::array<Position, 3> triangle;

  if (size < 3)
    return {false, triangle};
  else if (size == 3) {
    triangle = {polygon[0], polygon[1], polygon[2]};
    polygon.clear();
    return {true, triangle};
  } else {
    for (int i = 0; i < size; ++i) {
      triTest = false;
      triangle[0] = polygon[(i + size - 1) % size];
      triangle[1] = polygon[i];
      triangle[2] = polygon[(i + 1) % size];
      if (this->isConvex(triangle[0], triangle[1], triangle[2])) {
        for (const Position &point : polygon) {
          auto it = std::find(triangle.begin(), triangle.end(), point);

          if (it != triangle.end())
            continue;
          if (this->inTriangle(triangle[0], triangle[1], triangle[2], point)) {
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