#include "Rectangle.hh"
#include <limits>

Rectangle::Rectangle(const Position &tl, const Position &br) {
  this->edges[0] = tl;
  this->edges[1] = {br.x, tl.y};
  this->edges[2] = br;
  this->edges[3] = {tl.x, br.y};
  this->width = br.x - tl.x;
  this->height = br.y - tl.y;
}

void Rectangle::setInternTranslation(const sf::Vector2f &tr) {
  this->translation = tr;
}

const std::array<Position, 4> &Rectangle::getEdges() const {
  return this->edges;
}

void Rectangle::move(const sf::Vector2f &displacement) {
  for (auto &edge : this->edges) {
    edge.x += displacement.x;
    edge.y += displacement.y;
  }
}

void Rectangle::setPosition(const Position &pos) {
  this->edges[0] = pos;
  this->edges[1] = {pos.x + this->width, pos.y};
  this->edges[2] = pos + Position(this->width, this->height);
  this->edges[3] = {pos.x, pos.y + this->height};

  for (auto &edge : this->edges) {
    edge.x += this->translation.x;
    edge.y += this->translation.y;
  }
}

void Rectangle::rotate(double angle) {
  Position copy;
  angle *= radianConvert;
  double cs = std::cos(angle);
  double sn = std::sin(angle);
  Position position(
      this->edges[0].x + (this->edges[2].x - this->edges[0].x) / 2.f,
      this->edges[0].y + (this->edges[2].y - this->edges[0].y) / 2.f);

  for (auto &edge : this->edges) {
    copy.x = edge.x - position.x;
    copy.y = edge.y - position.y;
    edge.x = copy.x * cs - copy.y * sn;
    edge.y = copy.x * sn + copy.y * cs;
    edge += position;
  }
}

// bool Rectangle::centerInRect(const std::array<>& edges) const {
//   sf::Vector2f AB = {}
// }

bool Rectangle::intersects(const Rectangle &rect) const {
  const auto &edges = rect.getEdges();
  //
  // if (this->centerInRect(edges))
  //   return true;
  for (int rectId = 0; rectId < 2; ++rectId) {
    const auto &cuEdges = (rectId == 0 ? this->edges : edges);

    for (unsigned int i = 0; i < cuEdges.size(); ++i) {
      int j = (i + 1) % cuEdges.size();
      sf::Vector2f normal(cuEdges[j].y - cuEdges[i].y,
                          cuEdges[i].x - cuEdges[j].x);
      double minA = std::numeric_limits<double>::max();
      double minB = std::numeric_limits<double>::max();
      double maxA = std::numeric_limits<double>::min();
      double maxB = std::numeric_limits<double>::min();

      for (const auto &edge : this->edges) {
        double projected = normal.x * edge.x + normal.y * edge.y;

        if (projected < minA)
          minA = projected;
        if (projected > maxA)
          maxA = projected;
      }
      for (const auto &edge : edges) {
        double projected = normal.x * edge.x + normal.y * edge.y;

        if (projected < minB)
          minB = projected;
        if (projected > maxB)
          maxB = projected;
      }
      if (maxA < minB || maxB < minA)
        return false;
    }
  }
  return true;
}

float Rectangle::getWidth() const { return this->width; }

float Rectangle::getHeight() const { return this->height; }