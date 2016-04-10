#ifndef TANK_VERTICESCALCULATOR_HH
#define TANK_VERTICESCALCULATOR_HH

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

class VerticesCalculator {
private:
  enum StepDirection { None, N, W, S, E };

public:
  VerticesCalculator() = default;
  VerticesCalculator(const sf::Sprite &sprite);

  ~VerticesCalculator() = default;
  VerticesCalculator(const VerticesCalculator &other) = default;
  VerticesCalculator(VerticesCalculator &&other) = default;
  VerticesCalculator &operator=(const VerticesCalculator &other) {
    this->previousStep = other.previousStep;
    this->nextStep = other.nextStep;
    this->directions = other.directions;
    this->data = other.data;
    this->width = other.width;
    this->height = other.height;
    return *this;
  };
  VerticesCalculator &operator=(VerticesCalculator &&other) {
    this->previousStep = other.previousStep;
    this->nextStep = other.nextStep;
    this->directions = other.directions;
    this->data = other.data;
    this->width = other.width;
    this->height = other.height;
    return *this;
  };

  void computeVertices();
  sf::VertexArray getLines() const;

private:
  sf::Vector2i findStartPoint();
  void walkPerimeter(int x, int y);
  void step(int x, int y);
  bool isPixelSolid(int x, int y) const;
  int getPixelState(int x, int y) const;

private:
  sf::VertexArray lines;
  StepDirection previousStep;
  StepDirection nextStep;
  std::array<StepDirection, 16> directions;
  std::vector<sf::Vector2i> contour;
  sf::Image data;
  int width;
  int height;
};

#endif /* end of include guard: TANK_VERTICESCALCULATOR_HH */
