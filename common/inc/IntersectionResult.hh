#ifndef INTERSECTIONRESULT_HH_
#define INTERSECTIONRESULT_HH_

struct intersectionResult {
  bool intersects;
  sf::Vector2f faceNormal;
  float distance;

  intersectionResult(bool intersects = true) : intersects(intersects) {}
};

#endif /* end of include guard: INTERSECTIONRESULT_HH_ */
