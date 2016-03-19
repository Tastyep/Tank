#ifndef TANK_CLIENTMAIN_HH
#define TANK_CLIENTMAIN_HH

#include "Map.hh"
#include "Settings.hh"
#include "TileManager.hh"

#include <SFML/Graphics.hpp>

class ClientMain {
public:
  ClientMain(const Settings &settings);

  ~ClientMain() = default;
  ClientMain(const ClientMain &other) = default;
  ClientMain(ClientMain &&other) = default;
  ClientMain &operator=(const ClientMain &other) = default;
  ClientMain &operator=(ClientMain &&other) = default;

  void run();
  void loadMap();

private:
  Settings settings;
  TileManager tileManager;
  Map map;
  sf::RenderWindow window;
};

#endif /* end of include guard: TANK_CLIENTMAIN_HH */
