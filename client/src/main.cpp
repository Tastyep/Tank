#include "ClientMain.hh"
#include "Parser.hh"
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[]) {
  std::srand(std::time(0));
  Settings set;
  Parser parser(set);

  parser.loadConfigFile("./config/config.cfg");
  ClientMain client(set);

  client.loadMap();
  client.run();
  return 0;
}