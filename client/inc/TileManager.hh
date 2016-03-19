#ifndef TANK_TILEMANAGER_HH_
#define TANK_TILEMANAGER_HH_

#include <SFML/Graphics.hpp>
#include <vector>

enum class TileId { Wall = 0, Last };

class TileManager {
public:
  TileManager(unsigned int tileSize = 64);

  ~TileManager() = default;
  TileManager(const TileManager &other) = default;
  TileManager(TileManager &&other) = default;
  TileManager &operator=(const TileManager &other) = default;
  TileManager &operator=(TileManager &&other) = default;

  const sf::Sprite &getTile(TileId id) const;

private:
  std::vector<sf::Sprite> gameTiles;
  unsigned int tileSize;
};

#endif /* end of include guard: TANK_TILEMANAGER_HH_ */
