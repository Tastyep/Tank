#ifndef TANK_TILEMANAGER_HH_
#define TANK_TILEMANAGER_HH_

#include "ACvar.hh"
#include "EntityId.hpp"
#include "Position.hpp"
#include "SpriteCollision.hh"
#include <vector>

class TileManager {
public:
  TileManager(ACvar &cvarList, unsigned int tileSize = 32);

  ~TileManager() = default;
  TileManager(const TileManager &other) = default;
  TileManager(TileManager &&other) = default;
  TileManager &operator=(const TileManager &other) = default;
  TileManager &operator=(TileManager &&other) = default;

  const sf::Sprite &getTile(EntityId id) const;
  int getTileSize() const;
  const SpriteCollision &getSpriteCollisionObject(EntityId id) const;

private:
  std::vector<sf::Sprite> gameTiles;
  std::vector<SpriteCollision> spriteCollisions;
  unsigned int tileSize;
};

#endif /* end of include guard: TANK_TILEMANAGER_HH_ */
