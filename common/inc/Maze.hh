#ifndef TANK_MAZE_HH
#define TANK_MAZE_HH

#include "Entity.hpp"

#include <array>
#include <vector>

class Maze {
public:
  struct MazeElement {
    Entity value;
    int dir;

    MazeElement() : value(Entity::Wall), dir(0) {}
  };

  struct Direction {
    int x;
    int y;
  };

public:
  Maze(int height, int width, int straightRate = 50);

  ~Maze() = default;
  Maze(const Maze &other) = default;
  Maze(Maze &&other) = default;
  Maze &operator=(const Maze &other) = default;
  Maze &operator=(Maze &&other) = default;

  void generate(unsigned int seed);
  const std::vector<std::vector<MazeElement>> &getMap() const;

private:
  void backtrackPath(int posX, int posY, int dirX, int dirY);
  int choseDirection(const std::vector<int> &dirIds) const;
  int getDirection(int dirX, int dirY) const;

private:
  std::vector<std::vector<MazeElement>> map;
  std::array<Direction, 4> directions;
  int width;
  int height;
  unsigned int straightRate;
};

#endif /* end of include guard: TANK_MAZE_HH */
