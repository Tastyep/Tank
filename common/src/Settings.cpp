#include "Settings.hh"

CvarList &Settings::getCvarList() { return this->vars; }

Controls &Settings::getControls() { return this->ctrl; }