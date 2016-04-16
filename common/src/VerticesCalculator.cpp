#include "VerticesCalculator.hh"
#include <cmath>
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

void VerticesCalculator::triangulate() {
  std::array<Position, 3> ear;
  bool success;

  do {
    auto pair = this->triangulation.getEar(this->vertices);
    success = pair.first;
    ear = pair.second;
    if (success) {
      std::cout << ear[0] << " " << ear[1] << " " << ear[2] << std::endl;
    }
  } while (success);
  std::cout << std::endl;
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

  while (!converted) {
    cu = this->contour[i];
    // std::cout << "Cu: " << cu.x << " " << cu.y << "\n";
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
        // std::cout << prev.x << " " << prev.y << " | " << cu.x << " " << cu.y
        //           << " angle: " << angle << "\n";
        if (angle > VerticesCalculator::maxAngle) {
          if (inter.first == this->vertices.front())
            converted = true;
          else {
            this->vertices.push_back(inter.first);
            newInter = true;
            first = inter.second;
            direction = inter.second - inter.first;
            //   std::cout << "New direction: " << direction.x << " " <<
            //   direction.y
            //             << "\n";
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

void VerticesCalculator::removeSteps() {
  std::vector<Position> toRemove;
  bool prevDeleted = false;

  for (int i = 0; i < static_cast<int>(this->contour.size()); ++i) {
    const Position &prev =
        this->contour[(this->contour.size() + i - 1) % this->contour.size()];
    const Position &next = this->contour[(i + 1) % this->contour.size()];
    if (prevDeleted == true) {
      prevDeleted = false;
      continue;
    }

    sf::Vector2f direction = next - prev;
    if (direction.x != 0 && direction.y != 0) { // means it is a diagonal
      toRemove.push_back(this->contour[i]);
      prevDeleted = true;
    }
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

  for (pos.y = 0; pos.y < this->bound.height; ++pos.y) {
    for (pos.x = 0; pos.x < this->bound.width; ++pos.x) {
      state = this->getPixelState(pos.x, pos.y);
      if (state != 0 && state != 15)
        return pos;
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

void VerticesCalculator::step(int x, int y) {
  int state = this->getPixelState(x, y);

  this->contour.emplace_back(x, y);
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

bool VerticesCalculator::isPixelSolid(int x, int y) const {
  if (x < 0 || y < 0 || x >= this->bound.width || y >= this->bound.height)
    return false;

  return (this->data.getPixel(x + bound.left, y + bound.top).a > 0);
}

void VerticesCalculator::move(const sf::Vector2f &displacement) {
  this->position.x += displacement.x;
  this->position.y += displacement.y;
  for (auto &point : this->vertices) {
    point += displacement;
  }
}

bool VerticesCalculator::intersects(const std::vector<Position> &points) const {

  for (int polygonId = 0; polygonId < 2; ++polygonId) {
    const auto &cuPoints = (polygonId == 0 ? this->vertices : points);

    for (unsigned int i = 0; i < cuPoints.size(); ++i) {
      int j = (i + 1) % cuPoints.size();
      sf::Vector2f normal(cuPoints[j].y - cuPoints[i].y,
                          cuPoints[i].x - cuPoints[j].x);
      double minA = std::numeric_limits<double>::max();
      double minB = std::numeric_limits<double>::max();
      double maxA = std::numeric_limits<double>::min();
      double maxB = std::numeric_limits<double>::min();

      for (const auto &point : this->vertices) {
        double projected = normal.x * point.x + normal.y * point.y;

        if (projected < minA)
          minA = projected;
        if (projected > maxA)
          maxA = projected;
      }
      for (const auto &point : points) {
        double projected = normal.x * point.x + normal.y * point.y;

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

void VerticesCalculator::setPosition(const Position &pos) {
  Position allignedPos = pos;
  this->position = pos;

  allignedPos.x -= this->bound.width / 2;
  allignedPos.y -= this->bound.height / 2;

  for (auto &point : this->vertices) {
    point.x += allignedPos.x;
    point.y += allignedPos.y;
  }
}

void VerticesCalculator::rotate(double angle) {
  Position copy;
  angle *= (VerticesCalculator::pi / 180.f);
  double cs = std::cos(angle);
  double sn = std::sin(angle);

  for (auto &point : this->vertices) {
    copy.x = point.x - this->position.x;
    copy.y = point.y - this->position.y;
    point.x = copy.x * cs - copy.y * sn;
    point.y = copy.x * sn + copy.y * cs;
    point.x += this->position.x;
    point.y += this->position.y;
  }
}

const std::vector<Position> &VerticesCalculator::getVertices() const {
  return this->vertices;
}