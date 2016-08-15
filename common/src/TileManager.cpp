#include "TileManager.hh"
#include "TextureManager.hpp"

#include <iostream>

TileManager::TileManager(ACvar &cvarList, unsigned int tileSize)
    : verticesCalculator(10), tileSize(tileSize) {
  auto &tm = TextureManager<>::instance();
  unsigned int tileId = 0;
  unsigned int nbTile = static_cast<unsigned int>(
      EntityId::Empty); // Empty represents the last element
  float maxFaceAngle = std::stof(cvarList.getCvar("cg_maxFaceAngle"));

  std::shared_ptr<sf::Texture> gameTexture =
      tm.load("../client/assets/asset.png", "GameAssets");
  sf::Vector2u textureSize = gameTexture->getSize();

  this->gameTiles.reserve(nbTile);
  for (unsigned int y = 0; y < textureSize.y && tileId < nbTile;
       y += this->tileSize) {
    for (unsigned int x = 0; x < textureSize.x && tileId < nbTile;
         x += this->tileSize) {
      sf::Sprite sprite(*gameTexture,
                        sf::IntRect(x, y, this->tileSize, this->tileSize));
      this->gameTiles.push_back(sprite);
      this->verticesCalculator.computeVertices(sprite);
      this->entityBodies.emplace_back(this->verticesCalculator.getPolygons(),
                                      this->verticesCalculator.getSpriteBound(),
                                      sprite.getTextureRect());
      ++tileId;
    }
  }
}

int TileManager::getTileSize() const { return this->tileSize; }

const sf::Sprite &TileManager::getTile(EntityId id) const {
  return this->gameTiles[static_cast<int>(id)];
}

const EntityBody &TileManager::getEntityBody(EntityId id) const {
  return this->entityBodies[static_cast<int>(id)];
}
