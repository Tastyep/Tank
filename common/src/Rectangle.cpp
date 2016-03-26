#include "Rectangle.hh"

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
    copy = edge - position;
    edge.x = copy.x * cs - copy.y * sn;
    edge.y = copy.x * sn + copy.y * cs;
    edge += position;
  }
}

bool Rectangle::intersects(const Rectangle &rect) const {
  const auto &edges = rect.getEdges();
  const auto &rectEdges = rect.getEdges();

  for (int rectId = 0; rectId < 2; ++rectId) {
    const auto &cuEdges = (rectId == 0 ? edges : rectEdges);

    for (unsigned int i = 0; i < cuEdges.size(); ++i) {
      int j = (i + 1) % cuEdges.size();
      double normalx = cuEdges[j].y - cuEdges[i].y;
      double normaly = cuEdges[j].x - cuEdges[i].x;
      Position minmaxA;
      Position minmaxB;

      for (const auto &edge : edges) {
        double projected = normalx * edge.x + normaly * edge.y;

        if (projected < minmaxA.x)
          minmaxA.x = projected;
        if (projected > minmaxA.y)
          minmaxA.y = projected;
      }
      for (const auto &edge : rectEdges) {
        double projected = normalx * edge.x + normaly * edge.y;

        if (projected < minmaxB.x)
          minmaxB.x = projected;
        if (projected > minmaxB.y)
          minmaxB.y = projected;
      }
      if (minmaxA.y < minmaxB.x || minmaxB.y < minmaxA.x)
        return false;
    }
  }
  return true;
}