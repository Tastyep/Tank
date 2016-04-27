#include "CvarList.hh"

CvarList::CvarList() {
  addCvar("r_width", new Cvar({"1", "1920"}, "600", "1600", Number));
  addCvar("r_height", new Cvar({"1", "1080"}, "800", "900", Number));
  addCvar("cl_name", new Cvar({}, "DefaultName", "DefaultName", String,
                              Restriction::None));
  addCvar("com_displayFps", new Cvar({"1", "1000"}, "60", "60", Number));
  addCvar("com_gameFps", new Cvar({"20", "300"}, "125", "125", Number));
  addCvar("net_upBandwidth",
          new Cvar({"0", "2147483647"}, "60000", "60000", Number));
  addCvar("net_downBandwidth",
          new Cvar({"0", "2147483647"}, "1000000", "1000000", Number));
  addCvar("sv_masterIP", new Cvar({"127.0.0.1", "62.210.136.56"}, "127.0.0.1",
                                  "127.0.0.1", String, Restriction::Value));
  addCvar("sv_masterPort",
          new Cvar({"25255"}, "25255", "25255", String, Restriction::Value));
  addCvar("sv_mapX", new Cvar({"3", "40"}, "20", "20", Number));
  addCvar("sv_mapY", new Cvar({"3", "40"}, "20", "20", Number));
  addCvar("sv_mapLinearity", new Cvar({"0", "100"}, "80", "80", Number));
  addCvar("sv_mapDensity", new Cvar({"0", "100"}, "80", "80", Number));
  addCvar("sv_mapSeed", new Cvar({"0", "2147483647"}, "0", "0", Number));
  addCvar("cg_maxFaceAngle", new Cvar({"5", "85"}, "10", "10", Number));
}
