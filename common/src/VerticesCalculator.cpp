#include "VerticesCalculator.hh"
#include <cmath>
#include <functional>
#include <stdexcept>

#include <iostream>
VerticesCalculator::VerticesCalculator(const sf::Sprite &sprite)
    : previousStep(StepDirection::None), nextStep(StepDirection::None) {
  const sf::Texture *texture = sprite.getTexture();
  this->bound = sprite.getTextureRect();

  this->data = texture->copyToImage();
  /*
  12
  48
  */
  this->directions = {StepDirection::None, StepDirection::N, StepDirection::E,
                      StepDirection::E,    StepDirection::W, StepDirection::N,
                      StepDirection::None, StepDirection::E, StepDirection::S,
                      StepDirection::None, StepDirection::S, StepDirection::S,
                      StepDirection::W,    StepDirection::N, StepDirection::W,
                      StepDirection::None};
}

void VerticesCalculator::computeVertices() {
  sf::Vector2i start = this->findStartPoint();

  this->walkPerimeter(start.x, start.y);
  this->removeSteps();
  this->polygonize();
  this->triangulate();
}

void VerticesCalculator::mergeTriangles(std::vector<Polygon> &polygons) {
  while (!polygons.empty()) {
    for (int i = 0; i < static_cast<int>(polygons.size()); ++i) {
      for (int v = 0; v < static_cast<int>(polygons[i].size()); ++v) {
        auto &polygon = polygons[i];
        int next = (v + 1) % polygon.size();

        auto it = std::find_if(
            polygons.begin(), polygons.end(),
            [&polygon, v, next](const auto &cuPolygon) {
              return (std::addressof(cuPolygon) != std::addressof(polygon) &&
                      cuPolygon.hasFace(polygon[v], polygon[next]));
            });
        if (it != polygons.end()) {
          int fIdx = it->getVerticeIdx(polygon[next]);
          int sIdx = it->getVerticeIdx(polygon[v]);
          Triangle top({polygon[v - 1], polygon[v], (*it)[sIdx + 1]});
          Triangle bottom({(*it)[fIdx - 1], polygon[next], polygon[next + 1]});

          bool topConvex = top.isConvex();
          bool bottomConvex = bottom.isConvex();

          if (topConvex &&
              bottomConvex) { // resulting polygon will be convex too
            const auto &vertices = polygon.getVertices();
            std::vector<Position> newVertices(vertices.begin(),
                                              vertices.begin() + v + 1);

            sIdx = (sIdx + 1) % it->size();
            while (sIdx != fIdx) {
              newVertices.push_back((*it)[sIdx]);
              sIdx = (sIdx + 1) % it->size();
            }
            // Insert points after next
            if (next > v)
              newVertices.insert(newVertices.end(), vertices.begin() + next,
                                 vertices.end());
            // Replace the polygon's vertices by newVertices
            polygon << newVertices;
            // Try again to expand the polygon
            v = -1;
            // Remove the merged polygon
            polygons.erase(it);
            if (std::distance(polygons.begin(), it) <
                i) { // If the point of erase is before our i
              --i;
            }
          }
        }
      }
      this->polygons.push_back(polygons[i]);
      polygons.erase(polygons.begin() + i);
    }
  }
}

void VerticesCalculator::triangulate() {
  std::vector<Polygon> triangles;
  bool success;

  do {
    auto pair = this->triangulation.getEar(this->vertices);
    success = pair.first;
    if (success) {
      triangles.push_back(pair.second);
    }
  } while (success);
  this->mergeTriangles(triangles);
}

void VerticesCalculator::polygonize() {
  Position first;
  Position prev;
  Position cu;
  sf::Vector2f direction;
  sf::Vector2f cuDirection;
  std::pair<Position, Position> inter;
  int interId = 0;
  bool newInter = true;
  int length = 0;
  float dotProduct;
  float norme;
  float angle;
  bool converted = false;
  int i = 0;

  if (contour.size() < 2)
    return;
  while (!converted) {
    cu = this->contour[i];
    if (this->vertices.empty()) {
      first = cu;

      this->vertices.push_back(first);
      length = 1;
      newInter = true;
      direction = this->contour[i + 1] - first;
    } else {
      cuDirection = cu - first; // Get the new vector from the same origin first
      if (length > 1) {
        cuDirection.x /=
            static_cast<float>(length); // scale it into a 1-1 square
        cuDirection.y /= static_cast<float>(length);
      }
      if (direction.x == cuDirection.x &&
          direction.y == cuDirection.y) { // Means the two vectors are equal
        ++length;
      } else {
        if (newInter) {
          newInter = false;
          inter.first = prev;
          inter.second = cu;
          interId = i;
        }

        dotProduct = direction.x * cuDirection.x + direction.y * cuDirection.y;
        norme =
            std::sqrt(direction.x * direction.x + direction.y * direction.y) *
            std::sqrt(cuDirection.x * cuDirection.x +
                      cuDirection.y * cuDirection.y);
        angle =
            std::acos(dotProduct / norme) * (180.f / VerticesCalculator::pi);
        if (angle > VerticesCalculator::maxAngle) {
          if (inter.first == this->vertices.front())
            converted = true;
          else {
            this->vertices.push_back(inter.first);
            newInter = true;
            first = inter.second;
            direction = inter.second - inter.first;
            length = 1;
            i = interId;
            cu = this->contour[i];
          }
        } else
          ++length;
      }
    }
    i = (i + 1) % this->contour.size();
    prev = cu;
  }
  this->contour.clear();
}

bool VerticesCalculator::isPixelBorder(const Position &pos) const {
  bool top = this->isPixelSolid(pos.x, pos.y - 1);
  bool right = this->isPixelSolid(pos.x + 1, pos.y);
  bool down = this->isPixelSolid(pos.x, pos.y + 1);
  bool left = this->isPixelSolid(pos.x - 1, pos.y);

  return (!(top & right & down & left));
}

void VerticesCalculator::removeSteps() {
  std::vector<Position> toRemove;
  int prev;
  float dotProduct;
  sf::Vector2f BA, BC;

  prev = this->contour.size() - 1;
  for (int i = 0; i < static_cast<int>(this->contour.size()); ++i) {
    if (!this->isPixelBorder(
            this->contour[i])) { // means the pixel has only non
      // transparent pixel neighbors
      toRemove.push_back(this->contour[i]);
      continue;
    }
    BA = this->contour[prev] - this->contour[i];
    BC = this->contour[(i + 1) % this->contour.size()] - this->contour[i];
    dotProduct = BA.x * BC.x + BA.y * BC.y;
    if (dotProduct == 0) { // the two vectors are perpendicular, remove the edge
      toRemove.push_back(this->contour[i]);
      continue;
    }
    prev = i;
  }
  this->contour.erase(
      std::remove_if(this->contour.begin(), this->contour.end(),
                     [&toRemove](const Position &point) {
                       return (std::find(toRemove.begin(), toRemove.end(),
                                         point) != toRemove.end());
                     }),
      this->contour.end());
}

sf::Vector2i VerticesCalculator::findStartPoint() {
  sf::Vector2i pos;
  int state;

  for (pos.y = 0; pos.y < this->bound.height - 1; ++pos.y) {
    for (pos.x = 0; pos.x < this->bound.width - 1; ++pos.x) {
      if (this->isPixelSolid(pos.x, pos.y) &&
          !this->isPixelSolid(pos.x, pos.y - 1)) {
        --pos.y;
        return pos;
      }
      if (this->isPixelSolid(pos.x + 1, pos.y)) {
        return pos;
      }
    }
  }
  return {0, 0};
}

void VerticesCalculator::walkPerimeter(int startX, int startY) {
  int x = startX;
  int y = startY;

  do {
    this->step(x, y);

    switch (this->nextStep) {
    case StepDirection::N:
      --y;
      break;
    case StepDirection::W:
      --x;
      break;
    case StepDirection::S:
      ++y;
      break;
    case StepDirection::E:
      ++x;
      break;
    default:
      throw std::runtime_error("VerticesCalculator: Invalid Sprite");
      break;
    }
  } while (x != startX || y != startY);
}

int VerticesCalculator::getPixelState(int x, int y) const {
  int state = 0;
  bool upLeft = this->isPixelSolid(x, y);
  bool upRight = this->isPixelSolid(x + 1, y);
  bool downRight = this->isPixelSolid(x + 1, y + 1);
  bool downLeft = this->isPixelSolid(x, y + 1);

  state |= (upLeft | upRight << 1 | downRight << 3 | downLeft << 2);
  return state;
}

void VerticesCalculator::allignOnSprite(int x, int y) {
  if (this->isPixelSolid(x, y)) {
    if (this->contour.empty() ||
        (!this->contour.empty() && this->contour.back() != Position(x, y))) {
      this->contour.emplace_back(x, y);
    }
  } else {
    if (this->isPixelSolid(x + 1, y)) {
      if (this->contour.empty() ||
          (!this->contour.empty() &&
           this->contour.back() != Position(x + 1, y) &&
           this->contour.front() != Position(x + 1, y))) {
        this->contour.emplace_back(x + 1, y);
      }
    }
    if (this->isPixelSolid(x, y + 1)) {
      if (this->contour.empty() ||
          (!this->contour.empty() &&
           this->contour.back() != Position(x, y + 1) &&
           this->contour.front() != Position(x, y + 1))) {

        this->contour.emplace_back(x, y + 1);
      }
    }
  }
}

void VerticesCalculator::step(int x, int y) {
  int state = this->getPixelState(x, y);

  this->allignOnSprite(x, y);
  switch (state) {
  case 6:
    this->nextStep =
        (this->previousStep == StepDirection::N ? StepDirection::W
                                                : StepDirection::E);
    break;
  case 9:
    this->nextStep =
        (this->previousStep == StepDirection::E ? StepDirection::N
                                                : StepDirection::S);
    break;
  default:
    this->nextStep = this->directions[state];
    break;
  }
  this->previousStep = this->nextStep;
}

bool VerticesCalculator::isPixelSolid(int x, int y, bool out) const {
  if (x < 0 || y < 0 || x >= this->bound.width || y >= this->bound.height)
    return out;

  // Compare it to 10 not 0 because sometimes the alpha is set to 1 or 2 but is
  // not visible
  return (this->data.getPixel(x + bound.left, y + bound.top).a > 10);
}

void VerticesCalculator::move(const sf::Vector2f &displacement) {
  this->position.x += displacement.x;
  this->position.y += displacement.y;
  for (auto &polygon : this->polygons) {
    for (auto &point : polygon.getVertices()) {
      point += displacement;
    }
  }
}

bool VerticesCalculator::intersects(const Polygon &polygonA,
                                    const Polygon &polygonB) const {
  const auto &verticesA = polygonA.getVertices();
  const auto &verticesB = polygonB.getVertices();

  for (int id = 0; id < 2; ++id) {
    const auto &vertices = (id == 0 ? verticesA : verticesB);

    for (unsigned int i = 0; i < vertices.size(); ++i) {
      int j = (i + 1) % vertices.size();
      sf::Vector2f normal(vertices[j].y - vertices[i].y,
                          vertices[i].x - vertices[j].x);
      double minA = std::numeric_limits<double>::max();
      double minB = std::numeric_limits<double>::max();
      double maxA = std::numeric_limits<double>::min();
      double maxB = std::numeric_limits<double>::min();

      for (const auto &edge : verticesA) {
        double projected = normal.x * edge.x + normal.y * edge.y;

        if (projected < minA)
          minA = projected;
        if (projected > maxA)
          maxA = projected;
      }
      for (const auto &edge : verticesB) {
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

bool VerticesCalculator::intersects(
    const std::vector<Polygon> &polygons) const {

  for (const Polygon &polygonA : this->polygons) {
    for (const Polygon &polygonB : polygons) {
      if (this->intersects(polygonA, polygonB))
        return true;
    }
  }
  return false;
}

void VerticesCalculator::setPosition(const Position &pos) {
  Position allignedPos = pos;
  this->position = pos;

  allignedPos.x -= this->bound.width / 2;
  allignedPos.y -= this->bound.height / 2;
  for (auto &polygon : this->polygons) {
    for (auto &point : polygon.getVertices()) {
      point.x += allignedPos.x;
      point.y += allignedPos.y;
    }
  }
}

void VerticesCalculator::rotate(double angle) {
  Position copy;
  angle *= (VerticesCalculator::pi / 180.f);
  double cs = std::cos(angle);
  double sn = std::sin(angle);

  for (auto &polygon : this->polygons) {
    for (auto &point : polygon.getVertices()) {
      copy.x = point.x - this->position.x;
      copy.y = point.y - this->position.y;
      point.x = copy.x * cs - copy.y * sn;
      point.y = copy.x * sn + copy.y * cs;
      point.x += this->position.x;
      point.y += this->position.y;
    }
  }
}

const std::vector<Position> &VerticesCalculator::getVertices() const {
  return this->vertices;
}

const std::vector<Polygon> &VerticesCalculator::getPolygons() const {
  return this->polygons;
}