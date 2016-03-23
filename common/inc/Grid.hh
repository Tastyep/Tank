#ifndef TANK_GRID_HH
#define TANK_GRID_HH

#include "Cell.hh"

class Cell;

class Grid {
public:
  Grid(int width, int height);

  ~Grid() = default;
  Grid(const Grid &other) = default;
  Grid(Grid &&other) = default;
  Grid &operator=(const Grid &other) = default;
  Grid &operator=(Grid &&other) = default;

  Cell &getCell(int x, int y);
  bool checkCollision(const Position &position, const Entity &entity);
  int getHeight() const;
  int getWidth() const;

private:
  int width;
  int height;
  std::vector<std::vector<Cell>> cells;
};

#endif /* end of include guard: TANK_GRID_HH */
