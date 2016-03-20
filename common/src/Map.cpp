#include "Map.hh"
#include "Entities/Wall.hh"

Map::Map(int width, int height) : maze(width, height) {
  this->tileMap = {{{static_cast<int>(EntityId::WallFull),
                     static_cast<int>(EntityId::WallBALeft), 0}}};
  this->entitySpawner = {[this](const sf::Sprite &sprite, int yPos) {
    this->entities[yPos].emplace_back(new Wall(sprite));
  }};
}

void Map::convertWalls(std::vector<std::vector<Maze::MazeElement>> &mazeData) {
  int width = mazeData.front().size();
  int height = mazeData.size();
  std::array<Position, 4> checks = {{{0, -1}, {1, 0}, {0, 1}, {-1, 0}}};
  std::array<EntityId, 15> flagMap = {
      EntityId::WallFull,    EntityId::Wall3Top,    EntityId::Wall3Right,
      EntityId::WallTARight, EntityId::Wall3Bottom, EntityId::WallLine,
      EntityId::WallBARight, EntityId::Empty,       EntityId::Wall3Left,
      EntityId::WallTALeft,  EntityId::WallCol,     EntityId::Empty,
      EntityId::WallBALeft,  EntityId::WallLine,    EntityId::WallFull};
  int flag;
  int checkId;

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      if (mazeData[y][x].value == EntityId::WallFull) {
        checkId = 0;
        flag = 0;

        for (const auto &pos : checks) {
          if (x + pos.x < 0 || x + pos.x >= width || y + pos.y < 0 ||
              y + pos.y >= height ||
              mazeData[y + pos.y][x + pos.x].value == EntityId::Empty)
            flag |= (1 << checkId);
          ++checkId;
        }

        mazeData[y][x].value = flagMap[flag];
      }
    }
  }
}

void Map::convert(std::vector<std::vector<Maze::MazeElement>> mazeData,
                  const TileManager &tileManager) {
  this->convertWalls(mazeData);
  for (unsigned int y = 0; y < mazeData.size(); ++y) {
    for (unsigned int x = 0; x < mazeData[y].size(); ++x) {
      auto &elem = mazeData[y][x];

      if (elem.value != EntityId::Empty) {
        int tileId = static_cast<int>(elem.value);

        auto it = std::find_if(this->tileMap.begin(), this->tileMap.end(),
                               [tileId](const auto &tileData) {
                                 return (tileId >= tileData.min &&
                                         tileId <= tileData.max);
                               });
        if (it == this->tileMap.end())
          continue;
        this->entitySpawner[static_cast<int>(it->spawnerPos)](
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
  this->maze.generate(2);
  this->convert(this->maze.getMap(), tileManager);
}

void Map::draw(sf::RenderWindow &renderTarget) {
  for (auto &col : this->entities) {
    for (auto &ent : col) {
      ent->draw(renderTarget);
    }
  }
}