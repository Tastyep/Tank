#include "Map.hh"
#include "Entities/Player.hh"
#include "Entities/Wall.hh"

#include <iostream>

Map::Map(const ACvar &cvarList)
    : maze(std::stoi(cvarList.getCvar("sv_mapX")),
           std::stoi(cvarList.getCvar("sv_mapY")),
           std::stoi(cvarList.getCvar("sv_mapLinearity")),
           std::stoi(cvarList.getCvar("sv_mapDensity"))),
      grid(std::stoi(cvarList.getCvar("sv_mapX")),
           std::stoi(cvarList.getCvar("sv_mapY"))) {
  this->tileMap = {{{static_cast<int>(EntityId::WallFull),
                     static_cast<int>(EntityId::WallSquare), 0}}};
  this->entitySpawner = {[this](const EntityBody &body,
                                const sf::Sprite &sprite, int posX, int posY) {
    std::shared_ptr<Entity> ptr(new Wall(body, sprite));

    this->grid.getCell(posX, posY).addObject(ptr);
    return ptr;
  }};
}

void Map::convertWalls(std::vector<std::vector<Maze::MazeElement>> &mazeData) {
  int width = mazeData.front().size();
  int height = mazeData.size();
  std::array<Position, 4> checks = {{{0, -1}, {1, 0}, {0, 1}, {-1, 0}}};
  std::array<Position, 4> checksDiag = {{{-1, -1}, {1, -1}, {1, 1}, {-1, 1}}};
  std::array<EntityId, 16> flagMap = {
      EntityId::WallFull,    EntityId::Wall3Top,    EntityId::Wall3Right,
      EntityId::WallTARight, EntityId::Wall3Bottom, EntityId::WallLine,
      EntityId::WallBARight, EntityId::WallLine,    EntityId::Wall3Left,
      EntityId::WallTALeft,  EntityId::WallCol,     EntityId::WallCol,
      EntityId::WallBALeft,  EntityId::WallLine,    EntityId::WallCol,
      EntityId::WallSquare};
  int flag;
  int checkId;
  bool notFree;
  EntityId value;

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
        value = flagMap[flag];
        if (flagMap[flag] == EntityId::WallFull) {
          notFree = false;
          for (const auto &pos : checksDiag) {
            if (x + pos.x < 0 || x + pos.x >= width || y + pos.y < 0 ||
                y + pos.y >= height ||
                mazeData[y + pos.y][x + pos.x].value != EntityId::Empty) {
              notFree = true;
              break;
            }
          }
          if (notFree)
            value = EntityId::WallSquare;
        }
        mazeData[y][x].value = value;
      }
    }
  }
}

void Map::convert(std::vector<std::vector<Maze::MazeElement>> mazeData,
                  const TileManager &tileManager) {
  int tileSize = tileManager.getTileSize();

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
        auto object = this->entitySpawner[static_cast<int>(it->spawnerPos)](
            tileManager.getEntityBody(elem.value),
            tileManager.getTile(elem.value), x, y);

        object->setPosition({static_cast<float>(x * tileSize + tileSize / 2),
                             static_cast<float>(y * tileSize + tileSize / 2)});
      }
    }
  }
}

void Map::generate(const TileManager &tileManager, int seed) {
  this->maze.generate(seed);
  this->convert(this->maze.getMap(), tileManager);
}

void Map::createPlayer(const TileManager &tileManager,
                       IActionAnalyzer &actionAnalyzer) {
  /* Hard coded */
  int tileSize = tileManager.getTileSize();

  std::shared_ptr<Movable> player(
      new Player(tileManager.getEntityBody(EntityId::Tank),
                 tileManager.getTile(EntityId::Tank), actionAnalyzer,
                 tileManager.getEntityBody(EntityId::Ball),
                 tileManager.getTile(EntityId::Ball)));

  this->grid.getCell(1, 1).addObject(player);
  player->setPosition({static_cast<float>(tileSize + tileSize / 2),
                       static_cast<float>(tileSize + tileSize / 2)});
}

void Map::update(std::chrono::nanoseconds time) {
  int width = this->grid.getWidth();
  int height = this->grid.getHeight();

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      auto &cell = this->grid.getCell(x, y);

      cell.update(this->grid, time);
    }
  }
  this->grid.processQueue();
}

void Map::draw(sf::RenderTarget &renderTarget) {
  unsigned int width = this->grid.getWidth();
  unsigned int height = this->grid.getHeight();

  for (unsigned int y = 0; y < height; ++y) {
    for (unsigned int x = 0; x < width; ++x) {
      auto &cell = this->grid.getCell(x, y);
      auto &entities = cell.getObjects();
      auto &updatableEntities = cell.getMovableObjects();

      for (const auto &entity : entities)
        entity->draw(renderTarget);
      for (const auto &entity : updatableEntities)
        entity->draw(renderTarget);
    }
  }
}
