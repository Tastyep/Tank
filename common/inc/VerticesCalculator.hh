#ifndef TANK_VERTICESCALCULATOR_HH
#define TANK_VERTICESCALCULATOR_HH

#include "Position.hpp"
#include "Rectangle.hh"
#include "Triangulation.hh"
#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>

class VerticesCalculator {
private:
  enum StepDirection { None, N, W, S, E };
  static constexpr auto pi = std::acos(-1);

public:
  VerticesCalculator() = default;
  VerticesCalculator(float maxFaceAngle = 10);

  ~VerticesCalculator() = default;
  VerticesCalculator(const VerticesCalculator &other) = default;
  VerticesCalculator(VerticesCalculator &&other) = default;
  VerticesCalculator &operator=(const VerticesCalculator &other) = default;
  VerticesCalculator &operator=(VerticesCalculator &&other) = default;

  void computeVertices(const sf::Sprite &sprite);
  const std::vector<Polygon> &getPolygons() const;
  const Rectangle &getSpriteBound() const;

private:
  void init();
  void computeSpriteBound();
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

private:
  float maxFaceAngle;
  StepDirection previousStep;
  StepDirection nextStep;
  std::array<StepDirection, 16> directions;
  std::vector<Position> contour;
  std::vector<Position> vertices;
  sf::Image data;
  sf::IntRect bound;
  Triangulation triangulation;
  std::vector<Polygon> polygons;
  Rectangle spriteBound;
};

#endif /* end of include guard: TANK_VERTICESCALCULATOR_HH */
