#ifndef TANK_CLIENTMAIN_HH
#define TANK_CLIENTMAIN_HH

#include "Game.hh"
#include "Parser.hh"

class ClientMain {
public:
  ClientMain(Settings &settings);

  ~ClientMain() = default;
  ClientMain(const ClientMain &other) = default;
  ClientMain(ClientMain &&other) = default;
  ClientMain &operator=(const ClientMain &other) = default;
  ClientMain &operator=(ClientMain &&other) = default;

  void run();
  void loadMap();

private:
  Settings &settings;
  Parser parser;
  TileManager tileManager;
  Game game;
  sf::RenderWindow window;
};

#endif /* end of include guard: TANK_CLIENTMAIN_HH */
