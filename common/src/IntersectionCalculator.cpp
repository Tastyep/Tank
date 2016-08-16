#include "IntersectionCalculator.hh"
#include <iostream>

float IntersectionCalculator::dot(const sf::Vector2f &a,
                                  const sf::Vector2f &b) const {
  return a.x * b.x + a.y * b.y;
}

void IntersectionCalculator::projectPolygon(
    const sf::Vector2f &faceNormal, const std::vector<Position> &vertices,
    float &min, float &max) const {
  float dotProduct;

  for (const auto &edge : vertices) {
    // To project a point on an axis use the dot product
    dotProduct = faceNormal.x * edge.x + faceNormal.y * edge.y;

    if (dotProduct < min)
      min = dotProduct;
    if (dotProduct > max)
      max = dotProduct;
  }
}

bool IntersectionCalculator::testSimpleIntersection(
    const Polygon &polygonA, const Polygon &polygonB) const {
  const auto &verticesA = polygonA.getVertices();
  const auto &verticesB = polygonB.getVertices();
  const auto &axisA = polygonA.getAxis();
  const auto &axisB = polygonB.getAxis();

  for (int pId = 0; pId < 2; ++pId) {
    const auto &axis = (pId == 0 ? axisA : axisB);

    for (const auto &ax : axis) {
      float minA = std::numeric_limits<double>::max();
      float minB = std::numeric_limits<double>::max();
      float maxA = std::numeric_limits<double>::min();
      float maxB = std::numeric_limits<double>::min();

      this->projectPolygon(ax, verticesA, minA, maxA);
      this->projectPolygon(ax, verticesB, minB, maxB);

      if (minA > maxB || minB > maxA) { // Doesn't Overlaps
        return false;
      }
    }
  }
  return true;
}

intersectionResult
IntersectionCalculator::intersects(const Polygon &polygonA,
                                   const Polygon &polygonB) const {
  intersectionResult result;
  float intervalDistance;
  float minIntervalDistance = std::numeric_limits<float>::max();
  const auto &verticesA = polygonA.getVertices();
  const auto &verticesB = polygonB.getVertices();
  const auto &axisA = polygonA.getAxis();
  const auto &axisB = polygonB.getAxis();

  for (int pId = 0; pId < 2; ++pId) {
    const auto &axis = (pId == 0 ? axisA : axisB);

    for (const auto &ax : axis) {
      float minA = std::numeric_limits<double>::max();
      float minB = std::numeric_limits<double>::max();
      float maxA = std::numeric_limits<double>::min();
      float maxB = std::numeric_limits<double>::min();

      this->projectPolygon(ax, verticesA, minA, maxA);
      this->projectPolygon(ax, verticesB, minB, maxB);

      if (minA > maxB || minB > maxA) { // Doesn't Overlaps
        result.intersects = false;
        return result;
      } else {
        intervalDistance = std::min(maxA, maxB) - std::max(minA, minB);
        // std::cout << ax.x << " " << ax.y << " " << intervalDistance << " "
        //           << minIntervalDistance << "\n";
        if (intervalDistance < minIntervalDistance) {
          minIntervalDistance = intervalDistance;
          result.faceNormal = ax;
          result.distance = intervalDistance;
        }
      }
    }
  }
  return result;
}

intersectionResult IntersectionCalculator::intersects(
    const std::vector<Polygon> &polygonsA,
    const std::vector<Polygon> &polygonsB) const {
  bool intersects = false;
  intersectionResult inter;
  intersectionResult save(false);

  // std::cout << "TEST INTERSECTION"
  //           << "\n";
  for (const Polygon &polygonA : polygonsA) {
    for (const Polygon &polygonB : polygonsB) {
      inter = this->intersects(polygonA, polygonB);

      if (inter.intersects && intersects == false) {
        intersects = true;
        save = inter;
      }
    }
  }

  return save;
}

intersectionResult
IntersectionCalculator::testIntersection(const EntityBody &bodyA,
                                         const EntityBody &bodyB) const {
  if (this->testSimpleIntersection(bodyA.getBound(), bodyB.getBound())) {
    return this->intersects(bodyA.getPolygons(), bodyB.getPolygons());
  }
  return intersectionResult(false);
}
