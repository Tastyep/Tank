#ifndef TANK_SETTINGS_HH
#define TANK_SETTINGS_HH

#include "Controls.hh"
#include "CvarList.hh"

class Settings {
public:
  Settings() = default;
  ~Settings() = default;

  Settings(const Settings &other) = default;
  Settings(Settings &&other) = default;
  Settings &operator=(const Settings &other) = default;
  Settings &operator=(Settings &&other) = default;

  CvarList &getCvarList();
  Controls &getControls();

private:
  CvarList vars;
  Controls ctrl;
};

#endif /* end of include guard: TANK_SETTINGS_HH */
