#ifndef TANK_GRID_HH
#define TANK_GRID_HH

#include "Cell.hh"
#include "IntersectionCalculator.hh"
#include <queue>
#include <utility>

class Grid {
private:
  struct MoveInfo {
    unsigned int cellFrom;
    unsigned int cellTo;
    std::shared_ptr<Movable> object;

    MoveInfo(unsigned int cellFrom, unsigned int cellTo,
             std::shared_ptr<Movable> object)
        : cellFrom(cellFrom), cellTo(cellTo), object(object) {}
  };

public:
  Grid(int width, int height);

  ~Grid() = default;
  Grid(const Grid &other) = default;
  Grid(Grid &&other) = default;
  Grid &operator=(const Grid &other) = default;
  Grid &operator=(Grid &&other) = default;
  Cell &operator[](unsigned int cellId);

  Cell &getCell(int x, int y);
  Cell &getCell(unsigned int cellId);
  unsigned int getCellId(const Position &pos) const;
  bool checkCollision(Movable &entity);
  int getHeight() const;
  int getWidth() const;
  void processQueue();
  void addObjectToQueue(std::shared_ptr<Entity> object);
  void addObjectToQueue(std::shared_ptr<Movable> object);
  void moveObject(std::shared_ptr<Movable> object, const Position &oldPos,
                  const Position &newPos);

private:
  int width;
  int height;
  std::vector<std::vector<Cell>> cells;
  std::queue<std::shared_ptr<Entity>> objects;
  std::queue<std::shared_ptr<Movable>> movableObjects;
  std::queue<MoveInfo> moveQueue;
  IntersectionCalculator intersectionCalculator;
};

#endif /* end of include guard: TANK_GRID_HH */
