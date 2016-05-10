#ifndef TANK_VERTICESCALCULATOR_HH
#define TANK_VERTICESCALCULATOR_HH

#include "Position.hpp"
#include "Triangulation.hh"
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

struct intersectionResult {
  bool intersects;
  sf::Vector2f faceNormal;
  float distance;

  intersectionResult(bool intersects = true) : intersects(intersects) {}
};

class VerticesCalculator {
private:
  enum StepDirection { None, N, W, S, E };
  static constexpr auto pi = std::acos(-1);

public:
  VerticesCalculator() = default;
  VerticesCalculator(const sf::Sprite &sprite, float maxFaceAngle = 10);

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
  intersectionResult intersects(const std::vector<Polygon> &polygons) const;
  const std::vector<Polygon> &getPolygons() const;

private:
  sf::Vector2i findStartPoint();
  void walkPerimeter(int x, int y);
  void step(int x, int y);
  bool isPixelSolid(int x, int y, bool out = false) const;
  bool isPixelBorder(const Position &pos) const;
  int getPixelState(int x, int y) const;
  void removeSteps();
  void polygonize();
  void triangulate();
  void mergeTriangles(std::vector<Polygon> &polygons);
  void allignOnSprite(int x, int y);
  float dot(const sf::Vector2f &a, const sf::Vector2f &b) const;
  void normalize(sf::Vector2f &vec) const;
  void projectPolygon(const sf::Vector2f &faceNormal,
                      const std::vector<Position> &vertices, float &min,
                      float &max) const;
  float calculateIntervalDistance(float minA, float maxA, float minB,
                                  float maxB) const;
  intersectionResult intersects(const Polygon &polygonA,
                                const Polygon &polygonB) const;

private:
  float maxFaceAngle;
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
