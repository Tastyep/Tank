#include "Polygon.hh"
#include <algorithm>
#include <cmath>

Polygon::Polygon(const std::vector<Position> &vertices)
    : vertices(vertices), originVertices(vertices) {
  this->axis.resize(this->vertices.size());
  this->computeTranslation();
  this->computeAxis();
}

Position &Polygon::operator[](int idx) {
  if (idx < 0)
    idx += this->vertices.size();
  return this->vertices[idx % this->vertices.size()];
}

void Polygon::draw(sf::RenderTarget &renderTarget) const {
  sf::VertexArray varray(sf::LinesStrip);

  for (const auto &vertice : this->vertices) {
    varray.append(sf::Vertex(sf::Vector2f(vertice.x, vertice.y),
                             sf::Color(255, 255, 255)));
  }
  varray.append(sf::Vertex(sf::Vector2f(vertices.front().x, vertices.front().y),
                           sf::Color(255, 255, 255)));
  renderTarget.draw(varray);
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

unsigned int Polygon::size() const { return this->vertices.size(); }

void Polygon::setPosition(const Position &position) {
  unsigned int size = this->vertices.size();

  for (unsigned int i = 0; i < size; ++i) {
    vertices[i].x = originVertices[i].x + position.x;
    vertices[i].y = originVertices[i].y + position.y;
  }
}

void Polygon::move(const sf::Vector2f &displacement) {
  for (auto &point : this->vertices)
    point += displacement;
}

void Polygon::rotate(double cs, double sn, const Position &rotationCenter) {
  Position translatedPos;

  for (auto &point : this->vertices) {
    translatedPos.x = point.x - rotationCenter.x;
    translatedPos.y = point.y - rotationCenter.y;
    point.x = translatedPos.x * cs - translatedPos.y * sn;
    point.y = translatedPos.x * sn + translatedPos.y * cs;
    point.x += rotationCenter.x;
    point.y += rotationCenter.y;
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

void Polygon::computeAxis() {
  unsigned int i = 0;
  float length;

  for (unsigned int j = this->vertices.size() - 1; i < this->vertices.size();
       j = i, ++i) {
    auto &ax = this->axis[i];

    // Compute the normal from the two vertices
    ax = {-(vertices[i].y - vertices[j].y), vertices[i].x - vertices[j].x};

    // then norme it
    length = std::sqrt(ax.x * ax.x + ax.y * ax.y);
    ax.x /= length;
    ax.y /= length;
  }
}

const std::vector<sf::Vector2f> &Polygon::getAxis() const { return this->axis; }
