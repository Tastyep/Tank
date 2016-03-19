#include "ACvar.hh"
#include <algorithm>

bool ACvar::isCvar(const std::string &name) const {
  auto it = this->cvars.find(name);

  return it != this->cvars.end();
}

const std::vector<std::string> &
ACvar::getCvarInfo(const std::string &name) const {
  auto it = this->cvars.find(name);

  return it->second->restrictValue;
}

const std::string &ACvar::getCvar(const std::string &name) const {
  auto it = this->cvars.find(name);

  return it->second->value;
}

bool ACvar::addCvar(const std::string &name, Cvar *cvar) {
  auto ret = this->cvars.insert(std::pair<std::string, Cvar *>(name, cvar));

  return ret.second;
}

std::pair<bool, std::string> ACvar::setCvar(const std::string &name,
                                            const std::string &value) {
  auto it = this->cvars.find(name);
  Cvar *cvar;
  double numValue;

  if (it == this->cvars.end())
    return {false, "Cvar [" + name + "] doesn't exist"};
  cvar = it->second;
  if (cvar->restrictType != Restriction::None) {
    if (cvar->restrictType == Restriction::Value) {
      if (std::find(cvar->restrictValue.begin(), cvar->restrictValue.end(),
                    value) == cvar->restrictValue.end())
        return {false, "Value for " + name + " isn't correct, default: " +
                           *(cvar->restrictValue.begin())};
    } else if (cvar->restrictType == Restriction::Range) {
      if (cvar->type == String)
        return {false, "String value cvars can't have a Range restriction"};
      try {
        numValue = std::stod(value);
      } catch (const std::invalid_argument &ia) {
        return {false, " cvar's value must be a number"};
      }
      if (numValue < std::stod(*(cvar->restrictValue.begin())))
        return {false, "Value for " + name + ": " + value + ", minimum: " +
                           *(cvar->restrictValue.begin() + 1)};
      if (cvar->restrictValue.size() > 2 &&
          numValue > std::stod(*(cvar->restrictValue.begin() + 1)))
        return {false, "Value for " + name + ": " + value + ", maximum: " +
                           *(cvar->restrictValue.begin() + 2)};
    }
  }
  if (cvar->type == Number) // In case there are no restrictions
  {
    try {
      numValue = std::stod(value);
    } catch (const std::invalid_argument &ia) {
      return {false, "cvar's value must be a number"};
    }
  }
  cvar->value = value;
  return {true, ""};
}
