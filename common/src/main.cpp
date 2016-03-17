#include "Maze.hh"

#include <iostream>

int main(int argc, char *argv[]) {
  Maze m(15, 30, 30);

  m.generate(3);
  auto &map = m.getMap();

  for (auto &lines : map) {
    for (auto &cell : lines) {
      std::cout << (cell.value == Entity::Wall ? "x" : " ");
    }
    std::cout << std::endl;
  }
  return 0;
}