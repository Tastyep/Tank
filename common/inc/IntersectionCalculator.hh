#ifndef INTERSECTIONCALCULATOR_HH_
#define INTERSECTIONCALCULATOR_HH_

#include "EntityBody.hh"
#include "IntersectionResult.hh"
#include "Polygon.hh"
#include <SFML/Graphics.hpp>
#include <vector>

class IntersectionCalculator {
public:
  IntersectionCalculator() = default;

  ~IntersectionCalculator() = default;
  IntersectionCalculator(const IntersectionCalculator &other) = default;
  IntersectionCalculator(IntersectionCalculator &&other) = default;
  IntersectionCalculator &
  operator=(const IntersectionCalculator &other) = default;
  IntersectionCalculator &operator=(IntersectionCalculator &&other) = default;

public:
  intersectionResult testIntersection(const EntityBody &bodyA,
                                      const EntityBody &bodyB) const;

private:
  float dot(const sf::Vector2f &a, const sf::Vector2f &b) const;
  void projectPolygon(const sf::Vector2f &faceNormal,
                      const std::vector<Position> &vertices, float &min,
                      float &max) const;
  bool testSimpleIntersection(const Polygon &polygonA,
                              const Polygon &polygonB) const;
  intersectionResult intersects(const Polygon &polygonA,
                                const Polygon &polygonB) const;
  intersectionResult intersects(const std::vector<Polygon> &polygonsA,
                                const std::vector<Polygon> &polygonsB) const;
};

#endif /* end of include guard: INTERSECTIONCALCULATOR_HH_ */
