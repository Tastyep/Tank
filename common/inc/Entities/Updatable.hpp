#ifndef TANK_UPDATABLE_HH
#define TANK_UPDATABLE_HH

#include <chrono>

class Updatable {
public:
  virtual ~Updatable() = default;

  virtual void update(std::chrono::nanoseconds time) = 0;
};

#endif /* end of include guard: TANK_UPDATABLE_HH */
