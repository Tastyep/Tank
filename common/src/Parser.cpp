#include <fstream>
#include <iterator>
#include <sstream>

#include "Exception.hh"
#include "Parser.hh"
#include "StringUtils.hh"

Parser::Parser(Settings &set) : set(set) {
  this->parseKey["set"] = &Parser::setKeyword;
  this->parseKey["bind"] = &Parser::bindKeyword;
  this->parseKey["unbind"] = &Parser::unbindKeyword;
  this->parseKey["exec"] = &Parser::execKeyword;
}

void Parser::setKeyword(const std::vector<std::string> &tokens) {
  CvarList &vars = this->set.getCvarList();

  if (tokens.size() < 3)
    throw(Exception("Missing parameters for set command"));
  vars.setCvar(tokens[1], tokens[2]);
}

void Parser::bindKeyword(const std::vector<std::string> &tokens) {
  Controls &ctrl = this->set.getControls();
  Entry entry;
  Action act;

  if (tokens.size() < 3)
    throw(Exception("Missing parameters for bind command"));
  entry = ctrl.getKeyFromCode(tokens[1]);
  // MouseWheelDown is -1 same as sf::Keyboard::Unknown
  if (entry == ctrl::state::Unset)
    throw(Exception("Unknown key [" + tokens[1] + "]"));
  act = ctrl.getActionFromCode(tokens[2]);
  if (act == Action::Unknown)
    throw(Exception("Unknown Action [" + tokens[2] + "] for key [" + tokens[1] +
                    "]"));
  ctrl.bindKeyOnAction(entry, act);
}

void Parser::unbindKeyword(const std::vector<std::string> &tokens) {
  Controls &ctrl = this->set.getControls();
  Entry entry;
  Action act;

  if (tokens.size() < 2)
    throw(Exception("Missing parameters for bind command"));
  entry = ctrl.getKeyFromCode(tokens[1]);
  if (entry == ctrl::state::Unset)
    throw(Exception("Unknown key [" + tokens[1] + "]"));
  act = ctrl.getActionFromKey(entry);
  if (act == Action::Unknown)
    throw(Exception("Key [" + tokens[1] + "] is not bound"));
  ctrl.unbindKeyFromAction(entry, act);
}

void Parser::execKeyword(const std::vector<std::string> &tokens) {
  if (tokens.size() < 2)
    throw(Exception("Missing parameters for exec command"));
  loadConfigFile(tokens[1]);
}

void Parser::giveCvarInfo(const std::vector<std::string> &tokens) {
  CvarList &cvars = this->set.getCvarList();
  auto &cvarInfo = cvars.getCvarInfo(tokens[0]);
  const std::string &cvarValue = cvars.getCvar(tokens[0]);

  this->retVal.push_back(tokens[0] + " [" + cvarValue + "] [Def: " +
                         cvarInfo[0] + " | Min: " + cvarInfo[1] + " | Max: " +
                         cvarInfo[2] + "]");
}

void Parser::parseCommandLine(const std::string &cmd, bool isFile) {
  std::vector<std::string> tokens;
  StringUtils su;

  su.tokenString(cmd, tokens);
  if (tokens.empty())
    return;
  else if (tokens[0].at(0) == '/' || isFile == true) {
    if (tokens[0].at(0) == '/')
      tokens[0] = tokens[0].substr(1);

    auto elem = this->parseKey.find(tokens[0]);
    if (elem != this->parseKey.end())
      (this->*(elem->second))(tokens);
    else if (this->set.getCvarList().isCvar(tokens[0]))
      giveCvarInfo(tokens);
    else
      throw(Exception("Invalid Keyword [" + *tokens.begin() + "]"));
  }
}

const std::vector<std::string> &Parser::parseLine(const std::string &cmd,
                                                  bool isFile) {
  std::vector<std::string> elems;

  if (!isFile)
    this->retVal.clear();
  this->utils.split(cmd, ';', elems);
  for (auto &command : elems) {
    try {
      parseCommandLine(command, isFile);
    } catch (const Exception &e) {
      this->retVal.push_back(e.what());
    }
  }
  return this->retVal;
}

const std::vector<std::string> &
Parser::loadConfigFile(const std::string &filename) {
  std::ifstream file(filename.c_str());
  std::string line;
  std::vector<std::string> content;

  this->retVal.clear();
  if (file.is_open()) {
    while (std::getline(file, line))
      content.push_back(line);
    file.close();
  } else {
    this->retVal.push_back("File [" + filename + "] not found");
    return this->retVal;
  }
  for (const auto &it : content) {
    if (!parseLine(it, true).empty())
      return this->retVal;
  }
  return this->retVal;
}
