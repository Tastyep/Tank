#ifndef TANK_CELL_HH
#define TANK_CELL_HH

#include "Entities/Entity.hpp"
#include <memory>
#include <vector>

class Cell {
public:
  Cell() = default;

  ~Cell() = default;
  Cell(const Cell &other) = default;
  Cell(Cell &&other) = default;
  Cell &operator=(const Cell &other) = default;
  Cell &operator=(Cell &&other) = default;

  const std::vector<std::shared_ptr<Entity>> &getObjects();
  void removeObject(const Position &pos);
  void addObject(std::shared_ptr<Entity> object);

private:
  std::vector<std::shared_ptr<Entity>> objects;
};

#endif /* end of include guard: TANK_CELL_HH */
