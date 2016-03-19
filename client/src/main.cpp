#include "ClientMain.hh"
#include "Parser.hh"

int main(int argc, char *argv[]) {
  Settings set;
  Parser parser(set);

  parser.loadConfigFile("./config/config.cfg");
  ClientMain client(set);

  client.loadMap();
  client.run();
  return 0;
}