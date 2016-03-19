#include "ClientMain.hh"
#include "TimeHandling.hpp"

ClientMain::ClientMain(const Settings &settings)
    : settings(settings),
      window(sf::VideoMode(
                 std::stoi(this->settings.getCvarList().getCvar("r_width")),
                 std::stoi(this->settings.getCvarList().getCvar("r_height"))),
             "Tank") {}

void ClientMain::run() {
  Controls &ctrl = settings.getControls();
  int gameFps = std::stoi(settings.getCvarList().getCvar("com_gameFps"));
  sf::Event event;
  Entry entry;

  TimeHandling time((std::chrono::milliseconds(1000 / gameFps)));

  window.setFramerateLimit(gameFps);
  window.setVerticalSyncEnabled(true);
  time.start();

  while (window.isOpen()) {
    window.clear();
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        break;
      }
      entry.fill(event);
      if (event.type == sf::Event::KeyPressed ||
          event.type == sf::Event::MouseButtonPressed ||
          event.type == sf::Event::MouseWheelMoved) {
        if (event.type == sf::Event::KeyPressed ||
            event.type == sf::Event::MouseButtonPressed) {
          if (event.type == sf::Event::MouseButtonPressed)
            ctrl.mouseButtonPressed(event);
          ctrl.pressKey(entry);
        }
      } else if (event.type == sf::Event::KeyReleased ||
                 event.type == sf::Event::MouseButtonReleased)
        ctrl.releaseKey(entry);
      else if (event.type == sf::Event::MouseMoved)
        ctrl.mouseMoved(event);
    }
    time.endFrame();
    // draw stuff here
    window.display();
  }
}