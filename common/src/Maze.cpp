#include "Maze.hh"

#include <algorithm>
#include <iostream>

Maze::Maze(int height, int width, int straightRate, int density)
    : width(width + 2), height(height + 2), density(density),
      straightRate(straightRate) {
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
  bool changeDir;
  int dirIdx;

  this->map[posY][posX].value = EntityId::Empty;
  do {
    changeDir = true;
    dirIds.clear();
    dirIds.reserve(4);
    me.dir = 0;
    for (int i = 0; i < 4; ++i) {
      int nposX = posX + this->directions[i].x;
      int nposY = posY + this->directions[i].y;
      if (nposX <= 0 || nposX >= this->width - 1 || nposY <= 0 ||
          nposY >= this->height - 1) { // if out of the map
        continue;
      }
      if (this->map[nposY][nposX].value == EntityId::Empty) {
        continue;
      }
      toContinue = false;
      for (unsigned int j = 0; j < this->directions.size(); ++j) {
        if (j == static_cast<unsigned int>((i + 2) % 4))
          continue;
        if (this->map[nposY + this->directions[j].y]
                     [nposX + this->directions[j].x]
                         .value == EntityId::Empty) {
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
    dirIdx = this->getDirection(dirX, dirY);
    for (const auto &dir : dirIds) {
      if (dirIdx == dir)
        changeDir = false;
    }
    if (changeDir == false &&
        static_cast<unsigned int>(std::rand() % 100) < straightRate) {
      this->backtrackPath(posX + dirX, posY + dirY, dirX, dirY);
    } else {
      dirIdx = this->choseDirection(dirIds);
      int ndirX = this->directions[dirIdx].x;
      int ndirY = this->directions[dirIdx].y;
      this->backtrackPath(posX + ndirX, posY + ndirY, ndirX, ndirY);
    }
    me.dir ^= (1 >> dirIdx);
  } while (me.dir > 0);
}

bool Maze::findClosestElem(int &posX, int &posY, EntityId ent) const {
  if (this->map[posY][posX].value == ent) {
    return true;
  } else {
    for (int radius = 1;
         (radius < this->width - 2 || radius < this->height - 2); ++radius) {
      for (int tmpY = std::max(posY - radius, 1); tmpY <= posY + radius;
           ++tmpY) {
        if (tmpY >= this->height - 1)
          break;
        for (int tmpX = std::max(posX - radius, 1); tmpX <= posX + radius;
             ++tmpX) {
          if (tmpX >= this->width - 1)
            break;
          if (this->map[tmpY][tmpX].value == ent) {
            posX = tmpX;
            posY = tmpY;
            return true;
          }
        }
      }
    }
  }
  return false;
}

void Maze::removeWalls() {
  int nbWall = (this->height * this->width) / 2;
  int toRemove = (nbWall * (100 - density)) / 250;
  int posX;
  int posY;

  for (int i = 0; i < toRemove; ++i) {
    posX = 1 + std::rand() % (this->width - 2); // Minus size of the border
    posY = 1 + std::rand() % (this->height - 2);

    if (findClosestElem(posX, posY, EntityId::WallFull) == true) {
      this->map[posY][posX].value = EntityId::Empty;
    } else
      break;
  }
}

void Maze::generate(unsigned int seed) {
  std::srand(seed);

  this->backtrackPath(1, 1, 1, 0);
  this->removeWalls();
}

int Maze::getWidth() const { return this->width; }
int Maze::getHeight() const { return this->height; }

const std::vector<std::vector<Maze::MazeElement>> &Maze::getMap() const {
  return this->map;
}