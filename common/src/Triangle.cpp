#include "Triangle.hh"
#include <array>

Triangle::Triangle(const std::vector<Position> &vertices) : Polygon(vertices) {}

bool Triangle::contains(const Position &x) const {
  std::array<float, 3> barCoef = {0, 0, 0};
  float eps = 0.0000001;

  barCoef[0] = ((this->vertices[1].y - this->vertices[2].y) *
                    (x.x - this->vertices[2].x) +
                (this->vertices[2].x - this->vertices[1].x) *
                    (x.y - this->vertices[2].y)) /
               (((this->vertices[1].y - this->vertices[2].y) *
                     (this->vertices[0].x - this->vertices[2].x) +
                 (this->vertices[2].x - this->vertices[1].x) *
                     (this->vertices[0].y - this->vertices[2].y)) +
                eps);
  barCoef[1] = ((this->vertices[2].y - this->vertices[0].y) *
                    (x.x - this->vertices[2].x) +
                (this->vertices[0].x - this->vertices[2].x) *
                    (x.y - this->vertices[2].y)) /
               (((this->vertices[1].y - this->vertices[2].y) *
                     (this->vertices[0].x - this->vertices[2].x) +
                 (this->vertices[2].x - this->vertices[1].x) *
                     (this->vertices[0].y - this->vertices[2].y)) +
                eps);
  barCoef[2] = 1.f - barCoef[0] - barCoef[1];

  for (float coef : barCoef) {
    if (coef >= 1 || coef <= 0)
      return false;
  }
  return true;
}

bool Triangle::isVertice(const Position &point) const {
  return (point == this->vertices[0] || point == this->vertices[1] ||
          point == this->vertices[2]);
}
