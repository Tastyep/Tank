#ifndef TANK_UPDATABLE_HH
#define TANK_UPDATABLE_HH

#include "Grid.hh"
#include <chrono>

class Grid;

class Updatable {
public:
  virtual ~Updatable() = default;

  virtual void update(Grid &grid, std::chrono::nanoseconds time) = 0;
};

#endif /* end of include guard: TANK_UPDATABLE_HH */
