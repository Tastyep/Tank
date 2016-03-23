#ifndef TANK_TILEMANAGER_HH_
#define TANK_TILEMANAGER_HH_

#include "EntityId.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class TileManager {
public:
  TileManager(unsigned int tileSize = 32);

  ~TileManager() = default;
  TileManager(const TileManager &other) = default;
  TileManager(TileManager &&other) = default;
  TileManager &operator=(const TileManager &other) = default;
  TileManager &operator=(TileManager &&other) = default;

  const sf::Sprite &getTile(EntityId id) const;
  int getTileSize() const;

private:
  std::vector<sf::Sprite> gameTiles;
  unsigned int tileSize;
};

#endif /* end of include guard: TANK_TILEMANAGER_HH_ */
