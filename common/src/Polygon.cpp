#include "Polygon.hh"
#include <algorithm>
#include <cmath>

Polygon::Polygon(const std::vector<Position> &vertices)
    : vertices(vertices), originVertices(vertices) {
  this->computeTranslation();
}

Polygon::Polygon(const Polygon &other) {
  this->vertices = other.vertices;
  this->originVertices = other.originVertices;
  this->translation = other.translation;
};

void Polygon::operator=(const std::vector<Position> &vertices) {
  this->vertices = vertices;
  this->originVertices = vertices;
  this->computeTranslation();
};

Position &Polygon::operator[](int idx) {
  if (idx < 0)
    idx += this->vertices.size();
  return this->vertices[idx % this->vertices.size()];
}

bool Polygon::hasFace(const Position &a, const Position &b) const {
  int verticeIdx = this->getVerticeIdx(a);

  if (verticeIdx == -1)
    return false;
  return (this->vertices[(this->vertices.size() + verticeIdx - 1) %
                         this->vertices.size()] == b ||
          this->vertices[(verticeIdx + 1) % this->vertices.size()] == b);
}

// dot(A,B) = 1 ---> pointing exactly in the same direction
// dot(A,B) > 0 ---> "concave" (less than 90° angle between them)
// dot(A,B) = 0 ---> orthogonal
// dot(A,B) < 0 ---> "convex" (pointing away from each other)
// dot(A,B) = -1 ---> pointing exactly the opposite way

bool Polygon::isConvex() const {
  float zProduct;
  float dx1, dy1, dx2, dy2;

  for (unsigned int i = 0; i < this->vertices.size(); ++i) {
    auto &A = this->vertices[i];
    auto &B = this->vertices[(i + 1) % this->vertices.size()];
    auto &C = this->vertices[(i + 2) % this->vertices.size()];

    dx1 = A.x - B.x;
    dy1 = A.y - B.y;
    dx2 = C.x - B.x;
    dy2 = C.y - B.y;
    zProduct = dx1 * dy2 - dy1 * dx2;

    if (zProduct < 0)
      return false;
  }
  return true;
}

int Polygon::getVerticeIdx(const Position &vertice) const {
  auto it = std::find(this->vertices.begin(), this->vertices.end(), vertice);

  if (it == this->vertices.end())
    return -1;
  return std::distance(this->vertices.begin(), it);
}

const std::vector<Position> &Polygon::getOriginVertices() const {
  return this->originVertices;
}

const std::vector<Position> &Polygon::getVertices() const {
  return this->vertices;
}
std::vector<Position> &Polygon::getVertices() { return this->vertices; }

unsigned int Polygon::size() const { return this->vertices.size(); }

void Polygon::setPosition(const Position &position) {
  unsigned int size = this->vertices.size();

  for (unsigned int i = 0; i < size; ++i) {
    vertices[i].x = originVertices[i].x + position.x;
    vertices[i].y = originVertices[i].y + position.y;
  }
}

void Polygon::computeTranslation() {
  float minX = this->vertices.front().x;
  float minY = this->vertices.front().y;

  for (unsigned int i = 1; i < this->vertices.size(); ++i) {
    if (this->vertices[i].x < minX)
      minX = this->vertices[i].x;
    if (this->vertices[i].y < minY)
      minY = this->vertices[i].y;
  }
  this->translation = sf::Vector2f(minX, minY);
}

Position Polygon::getPosition() const {
  return this->position + this->translation;
}