#include "VerticesCalculator.hh"
#include <cmath>
#include <functional>
#include <stdexcept>

#include <iostream>
VerticesCalculator::VerticesCalculator(float maxFaceAngle)
    : maxFaceAngle(maxFaceAngle), previousStep(StepDirection::None),
      nextStep(StepDirection::None) {
  this->directions = {StepDirection::None, StepDirection::N, StepDirection::E,
                      StepDirection::E,    StepDirection::W, StepDirection::N,
                      StepDirection::None, StepDirection::E, StepDirection::S,
                      StepDirection::None, StepDirection::S, StepDirection::S,
                      StepDirection::W,    StepDirection::N, StepDirection::W,
                      StepDirection::None};
}

void VerticesCalculator::init() {
  this->previousStep = StepDirection::None;
  this->nextStep = StepDirection::None;
  this->contour.clear();
  this->vertices.clear();
  this->polygons.clear();
}

void VerticesCalculator::computeVertices(const sf::Sprite &sprite) {
  const sf::Texture *texture = sprite.getTexture();
  sf::Vector2i start;

  this->init();
  this->bound = sprite.getTextureRect();
  this->data = texture->copyToImage();
  this->computeSpriteBound();

  start = this->findStartPoint();
  this->walkPerimeter(start.x, start.y);
  // this->removeSteps();
  this->polygonize();
  Polygon polygon(this->vertices);

  if (polygon.isConvex()) {
    this->polygons.push_back(polygon);
    this->vertices.clear();
  } else {
    this->triangulate();
  }
}

void VerticesCalculator::computeSpriteBound() {
  sf::Color pixel;

  // init so br is tl & tl is br
  Position tl(this->bound.width, this->bound.height);
  Position br(0, 0);
  Position origin = Position(static_cast<float>(this->bound.width) / 2.f,
                             static_cast<float>(this->bound.height) / 2.f);
  for (int ty = 0; ty < this->bound.height; ++ty) {
    for (int tx = 0; tx < this->bound.width; ++tx) {
      if (this->isPixelSolid(
              tx, ty)) { // Not Transparent, function auto adds the offset
        pixel =
            this->data.getPixel(tx + this->bound.left, ty + this->bound.top);

        if (ty < tl.y)
          tl.y = ty;
        if (ty > br.y)
          br.y = ty;
        if (tx < tl.x)
          tl.x = tx;
        if (tx > br.x)
          br.x = tx;
      }
    }
  }
  tl.x -= origin.x;
  tl.y -= origin.y;
  br.x -= origin.x;
  br.y -= origin.y;
  this->spriteBound = Rectangle(tl, br);
  this->spriteBound.setInternTranslation({tl.x, tl.y});
}

void VerticesCalculator::mergeTriangles(std::vector<Polygon> &polygons) {
  // std::cout << "Enter"
  //           << "\n";
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
          //   if (not topConvex or not bottomConvex) {
          //     std::cout << "top/bottom: " << (int)topConvex << " "
          //               << (int)bottomConvex << std::endl
          //               << top << std::endl
          //               << std::endl
          //               << bottom << "\n";
          //   }

          if (topConvex &&
              bottomConvex) { // resulting polygon will be convex too
            const auto &vertices = polygon.getVertices();
            std::vector<Position> newVertices(vertices.begin(),
                                              vertices.begin() + v + 1);

            // std::cout << "Merge " << std::endl
            //           << polygon << " " << std::endl
            //           << *it << "\n";
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
            polygon = newVertices;
            // std::cout << "into: " << std::endl << polygon << "\n";
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
        if (angle > this->maxFaceAngle) {
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

const std::vector<Polygon> &VerticesCalculator::getPolygons() const {
  return this->polygons;
}

const Rectangle &VerticesCalculator::getSpriteBound() const {
  return this->spriteBound;
}
