#include "TileManager.hh"
#include "TextureManager.hpp"

TileManager::TileManager(unsigned int tileSize) : tileSize(tileSize) {
  auto &tm = TextureManager<>::instance();
  unsigned int tileId = 0;
  unsigned int nbTile = static_cast<unsigned int>(
      EntityId::Empty); // Empty represents the last element

  std::shared_ptr<sf::Texture> gameTexture =
      tm.load("../client/assets/asset.png", "GameAssets");
  sf::Vector2u textureSize = gameTexture->getSize();

  this->gameTiles.reserve(nbTile);
  for (unsigned int y = 0; y < textureSize.y && tileId < nbTile;
       y += this->tileSize) {
    for (unsigned int x = 0; x < textureSize.x && tileId < nbTile;
         x += this->tileSize) {
      this->gameTiles.emplace_back(
          *gameTexture,
          sf::IntRect(x, y, x + this->tileSize, y + this->tileSize));
    }
  }
}

const sf::Sprite &TileManager::getTile(EntityId id) const {
  return this->gameTiles[static_cast<int>(id)];
}