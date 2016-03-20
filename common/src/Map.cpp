#include "Map.hh"
#include "Entities/Wall.hh"

#include <iostream>

Map::Map(int width, int height) : maze(width, height) {
  this->entitySpawner = {[this](const sf::Sprite &sprite, int yPos) {
    this->entities[yPos].emplace_back(new Wall(sprite));
  }};
}

void Map::convert(const std::vector<std::vector<Maze::MazeElement>> &mazeData,
                  const TileManager &tileManager) {
  for (unsigned int y = 0; y < mazeData.size(); ++y) {
    for (unsigned int x = 0; x < mazeData[y].size(); ++x) {
      auto &elem = mazeData[y][x];

      if (elem.value != EntityId::Empty) {
        this->entitySpawner[static_cast<int>(elem.value)](
            tileManager.getTile(elem.value), y);
        this->entities[y].back()->setPosition(
            {static_cast<int>(x), static_cast<int>(y)});
      }
    }
  }
}

void Map::generate(const TileManager &tileManager) {
  int height = this->maze.getHeight();

  entities.clear();
  entities.resize(height);
  this->maze.generate(0);
  this->convert(this->maze.getMap(), tileManager);
}

void Map::draw(sf::RenderTarget &renderTarget) {
  for (auto &col : this->entities) {
    for (auto &ent : col) {
      ent->draw(renderTarget);
    }
  }
}