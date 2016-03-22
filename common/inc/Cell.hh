#ifndef TANK_CELL_HH
#define TANK_CELL_HH

#include "Entities/Entity.hpp"
#include "Entities/Movable.hh"
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
  const std::vector<std::shared_ptr<Movable>> &getMovableObjects();
  void removeObject(const Position &pos);
  void addObject(std::shared_ptr<Entity> object);
  void addObject(std::shared_ptr<Movable> object);

private:
  std::vector<std::shared_ptr<Entity>> objects;
  std::vector<std::shared_ptr<Movable>> movableObjects;
};

#endif /* end of include guard: TANK_CELL_HH */
