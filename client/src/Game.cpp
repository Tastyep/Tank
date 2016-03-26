#include "Game.hh"

// for debug
#include <iostream>

Game::Game(Settings &settings, TileManager &tileManager)
    : settings(settings), tileManager(tileManager), map(10, 10) {}

void Game::update(std::chrono::nanoseconds time) {
  this->actionAnalyzer.computeInputChanges(this->settings);
  this->map.update(time);
}

void Game::generateMap() {
  this->map.generate(this->tileManager);
  this->map.createPlayer(this->tileManager, this->actionAnalyzer);
}

void Game::draw(sf::RenderTarget &renderTarget) {
  this->map.draw(renderTarget);
}