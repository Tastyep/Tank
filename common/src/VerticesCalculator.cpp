#include "VerticesCalculator.hh"
#include <stdexcept>

#include <iostream>
VerticesCalculator::VerticesCalculator(const sf::Sprite &sprite)
    : lines(sf::LinesStrip), previousStep(StepDirection::None),
      nextStep(StepDirection::None) {
  const sf::Texture *texture = sprite.getTexture();
  const sf::IntRect &rect = sprite.getTextureRect();
  this->width = rect.width;
  this->height = rect.height;

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
}

sf::Vector2i VerticesCalculator::findStartPoint() {
  sf::Vector2i pos;
  int state;

  for (pos.y = 0; pos.y < this->height; ++pos.y) {
    for (pos.x = 0; pos.x < this->width; ++pos.x) {
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
  if (x < 0 || y < 0 || x >= this->width || y >= this->height)
    return false;

  return (this->data.getPixel(x, y).a > 0);
}

sf::VertexArray VerticesCalculator::getLines() const { return this->lines; }