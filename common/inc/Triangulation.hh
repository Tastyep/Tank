#ifndef TANK_TRIANGULATION_HH
#define TANK_TRIANGULATION_HH

#include "Position.hpp"
#include <array>

class Triangulation {
public:
  Triangulation() = default;

  ~Triangulation() = default;
  Triangulation(const Triangulation &other) = default;
  Triangulation(Triangulation &&other) = default;
  Triangulation &operator=(const Triangulation &other) = default;
  Triangulation &operator=(Triangulation &&other) = default;

  std::pair<bool, std::array<Position, 3>>
  getEar(std::vector<Position> &polygon) const;

private:
  bool isConvex(const Position &a, const Position &b, const Position &c) const;
  bool inTriangle(const Position &a, const Position &b, const Position &c,
                  const Position &x) const;
};

#endif /* end of include guard: TANK_TRIANGULATION_HH */
