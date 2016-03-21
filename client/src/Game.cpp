#include "Game.hh"

Game::Game(Settings &set, TileManager &tileManager)
    : set(set), tileManager(tileManager), map(40, 20) {}

void Game::update() {}

void Game::generateMap() { this->map.generate(this->tileManager); }

void Game::draw(sf::RenderTarget &renderTarget) {
  this->map.draw(renderTarget);
}