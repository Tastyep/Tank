#include "Game.hh"

// for debug
#include <iostream>

Game::Game(Settings &settings, TileManager &tileManager)
    : settings(settings), tileManager(tileManager),
      map(settings.getCvarList()) {}

void Game::update(std::chrono::nanoseconds time) {
  this->actionAnalyzer.computeInputChanges(this->settings);
  this->map.update(time);
}

void Game::generateMap() {
  this->map.generate(
      this->tileManager,
      std::stoi(this->settings.getCvarList().getCvar("sv_mapSeed")));
  this->map.createPlayer(this->tileManager, this->actionAnalyzer);
}

void Game::draw(sf::RenderTarget &renderTarget) {
  this->map.draw(renderTarget);
}