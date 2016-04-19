#ifndef TANK_VERTICESCALCULATOR_HH
#define TANK_VERTICESCALCULATOR_HH

#include "Position.hpp"
#include "Triangulation.hh"
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

class VerticesCalculator {
private:
  enum StepDirection { None, N, W, S, E };
  static constexpr auto pi = std::acos(-1);
  static constexpr float maxAngle = 10;

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
    this->bound = other.bound;
    this->contour = other.contour;
    this->vertices = other.vertices;
    this->position = other.position;
    this->polygons = other.polygons;
    return *this;
  };
  VerticesCalculator &operator=(VerticesCalculator &&other) {
    this->previousStep = other.previousStep;
    this->nextStep = other.nextStep;
    this->directions = other.directions;
    this->data = other.data;
    this->bound = other.bound;
    this->contour = other.contour;
    this->vertices = other.vertices;
    this->position = other.position;
    this->polygons = other.polygons;
    return *this;
  };

  void computeVertices();
  const std::vector<Position> &getVertices() const;
  void move(const sf::Vector2f &displacement);
  void setPosition(const Position &pos);
  void rotate(double angle);
  bool intersects(const std::vector<Polygon> &polygons) const;
  const std::vector<Polygon> &getPolygons() const;

private:
  sf::Vector2i findStartPoint();
  void walkPerimeter(int x, int y);
  void step(int x, int y);
  bool isPixelSolid(int x, int y) const;
  int getPixelState(int x, int y) const;
  void removeSteps();
  void polygonize();
  void triangulate();
  void mergeTriangles(std::vector<Polygon> &polygons);
  bool intersects(const Polygon &polygonA, const Polygon &polygonB) const;

private:
  StepDirection previousStep;
  StepDirection nextStep;
  std::array<StepDirection, 16> directions;
  std::vector<Position> contour;
  std::vector<Position> vertices;
  sf::Image data;
  sf::IntRect bound;
  Position position;
  Triangulation triangulation;
  std::vector<Polygon> polygons;
};

#endif /* end of include guard: TANK_VERTICESCALCULATOR_HH */
