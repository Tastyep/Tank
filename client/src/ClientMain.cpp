#include "ClientMain.hh"

ClientMain::ClientMain(const Settings &settings)
    : settings(settings),
      window(sf::VideoMode(
                 std::stoi(this->settings.getCvarList().getCvar("r_width")),
                 std::stoi(this->settings.getCvarList().getCvar("r_height"))),
             "Tank") {}

void ClientMain::run() {}