#ifndef TANK_TILEMANAGER_HH_
#define TANK_TILEMANAGER_HH_

#include "ACvar.hh"
#include "EntityBody.hh"
#include "EntityId.hpp"
#include "Position.hpp"
#include "VerticesCalculator.hh"
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
  const EntityBody &getEntityBody(EntityId id) const;

private:
  std::vector<sf::Sprite> gameTiles;
  std::vector<EntityBody> entityBodies;
  VerticesCalculator verticesCalculator;
  unsigned int tileSize;
};

#endif /* end of include guard: TANK_TILEMANAGER_HH_ */
