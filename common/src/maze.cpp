#include "Maze.hh"

#include <algorithm>
#include <iostream>

Maze::Maze(int height, int width, int straightRate)
    : width(width + 2), height(height + 2), straightRate(straightRate) {
  this->map.resize(this->height);
  this->directions = {{{0, -1}, {1, 0}, {0, 1}, {-1, 0}}};

  for (auto &lines : this->map) {
    lines.resize(this->width);
  }
}

int Maze::choseDirection(const std::vector<int> &dirIds) const {
  return dirIds[std::rand() % dirIds.size()];
}

int Maze::getDirection(int dirX, int dirY) const {
  int dir = 0;

  if (dirX != 0)
    ++dir;
  if (dirY == 1)
    dir += 2;
  return dir;
}

void Maze::backtrackPath(int posX, int posY, int dirX, int dirY) {
  MazeElement &me = this->map[posY][posX];
  std::vector<int> dirIds;
  bool toContinue = false;

  this->map[posY][posX].value = Entity::Empty;
  do {
    dirIds.clear();
    dirIds.reserve(4);
    me.dir = 0;
    for (int i = 0; i < 4; ++i) {
      int dir = this->getDirection(dirX, dirY);

      int nposX = posX + this->directions[i].x;
      int nposY = posY + this->directions[i].y;

      if (nposX <= 0 || nposX >= this->width - 1 || nposY <= 0 ||
          nposY >= this->height - 1) { // if out of the map
        continue;
      }
      if (this->map[nposY][nposX].value == Entity::Empty) {
        continue;
      }
      toContinue = false;
      for (int j = 0; j < this->directions.size(); ++j) {
        if (j == ((i + 2) % 4))
          continue;
        if (this->map[nposY + this->directions[j].y]
                     [nposX + this->directions[j].x]
                         .value == Entity::Empty) {
          toContinue = true;
          break;
        }
      }
      if (toContinue)
        continue;
      me.dir |= (1 << i);
      dirIds.push_back(i);
    }
    if (me.dir == 0)
      return;
    int dirIdx = this->choseDirection(dirIds);

    dirX = this->directions[dirIdx].x;
    dirY = this->directions[dirIdx].y;
    backtrackPath(posX + dirX, posY + dirY, dirX, dirY);
    me.dir ^= (1 >> dirIdx);
  } while (me.dir > 0);
}

const std::vector<std::vector<Maze::MazeElement>> &Maze::getMap() const {
  return this->map;
}

void Maze::generate(unsigned int seed) {
  std::srand(seed);

  this->backtrackPath(1, 1, 1, 0);
}