#include "Map.hh"
#include "Entities/Wall.hh"

Map::Map(int width, int height) : maze(width, height) {
  this->entitySpawner = {[this](const sf::Sprite &sprite, int yPos) {
    this->entities[yPos].emplace_back(new Wall(sprite));
  }};
}

void Map::convert(const std::vector<std::vector<Maze::MazeElement>> &mazeData) {
  for (unsigned int y = 0; y < mazeData.size(); ++y) {
    for (const auto &elem : mazeData[y]) {
      this->entitySpawner[static_cast<int>(elem.value)];
    }
  }
}

void Map::generate(const TileManager &tileManager) {
  entities.clear();
  this->maze.generate(0);
  this->convert(this->maze.getMap());
}