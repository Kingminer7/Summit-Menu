#include <Geode/Geode.hpp>
#include "LoadManager.hpp"

#include "Config.hpp"
namespace summit {
  matjson::Value Config::saved = nullptr;
  matjson::Value Config::temp = nullptr;

  bool Config::initialized = false;

  void Config::init() {
    if (initialized) return;
    auto mod = geode::Mod::get();
    saved = mod->getSavedValue<matjson::Value>("data", {});
    temp = {};
    initialized = true;
  }

  void Config::save() {
    if (!initialized) return;
    auto mod = geode::Mod::get();
    mod->setSavedValue<matjson::Value>("data", saved);
  }
}

$onLoad (Initial, -1000) {
  summit::Config::init();
}