#ifndef TANK_MAP_HH
#define TANK_MAP_HH

#include "Entities/Entity.hpp"
#include "Maze.hh"
#include "TileManager.hh"
#include <functional>
#include <memory>
#include <vector>

class Map {
private:
  struct TileData {
    int min;
    int max;
    int spawnerPos;
  };

public:
  Map(int height, int width);

  ~Map() = default;
  Map(const Map &other) = default;
  Map(Map &&other) = default;
  Map &operator=(const Map &other) = default;
  Map &operator=(Map &&other) = default;

  void generate(const TileManager &tileManager);
  void draw(sf::RenderWindow &renderTarget);

private:
  void convertWalls(std::vector<std::vector<Maze::MazeElement>> &mazeData);
  void convert(std::vector<std::vector<Maze::MazeElement>> mazeData,
               const TileManager &tileManager);

private:
  Maze maze;
  std::vector<TileData> tileMap;
  std::vector<std::function<void(const sf::Sprite &sprite, int yPos)>>
      entitySpawner;
  std::vector<std::vector<std::shared_ptr<Entity>>> entities;
};

#endif /* end of include guard: TANK_MAP_HH */
