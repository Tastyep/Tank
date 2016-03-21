#ifndef TANK_GAME_HH
#define TANK_GAME_HH

#include "ActionAnalyzer.hh"
#include "Map.hh"
#include "Settings.hh"
#include "TileManager.hh"

#include <SFML/Graphics.hpp>

class Game {
public:
  Game(Settings &set, TileManager &tileManager);

  ~Game() = default;
  Game(const Game &other) = default;
  Game(Game &&other) = default;
  Game &operator=(const Game &other) = default;
  Game &operator=(Game &&other) = default;

  void update();
  void draw(sf::RenderTarget &renderTarget);
  void generateMap();

private:
  Settings &set;
  TileManager &tileManager;
  Map map;
  ActionAnalyzer actionAnalyzer;
};

#endif /* end of include guard: TANK_GAME_HH */
