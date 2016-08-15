#ifndef TANK_GRID_HH
#define TANK_GRID_HH

#include "Cell.hh"
#include "IntersectionCalculator.hh"
#include <queue>

class Grid {
public:
  Grid(int width, int height);

  ~Grid() = default;
  Grid(const Grid &other) = default;
  Grid(Grid &&other) = default;
  Grid &operator=(const Grid &other) = default;
  Grid &operator=(Grid &&other) = default;

  Cell &getCell(int x, int y);
  bool checkCollision(Movable &entity);
  int getHeight() const;
  int getWidth() const;
  void processQueue();
  void addObjectToQueue(std::shared_ptr<Entity> object);
  void addObjectToQueue(std::shared_ptr<Movable> object);

private:
  int width;
  int height;
  std::vector<std::vector<Cell>> cells;
  std::queue<std::shared_ptr<Entity>> objects;
  std::queue<std::shared_ptr<Movable>> movableObjects;
  IntersectionCalculator intersectionCalculator;
};

#endif /* end of include guard: TANK_GRID_HH */
