#include "Config.hpp"

using namespace geode::prelude;

namespace summit {
bool Config::initialized = false;

matjson::Value Config::saved = matjson::makeObject({});
matjson::Value Config::temp = matjson::makeObject({});

matjson::Value Config::getAllSaved() {
  if (!initialized)
    init();
  return saved;
}

void Config::init() {
  if (initialized)
    return;
  saved = Mod::get()->getSavedValue<matjson::Value>("config",
                                                    matjson::makeObject({}));
  temp = matjson::makeObject({});
  initialized = true;
}

void Config::save() {
  if (!initialized)
    init();
  Mod::get()->setSavedValue<matjson::Value>("config", saved);
}

void Config::load(bool resetTemp) {
  if (!initialized)
    init();
  saved = Mod::get()->getSavedValue<matjson::Value>("config",
                                                    matjson::makeObject({}));
  if (resetTemp)
    temp = matjson::makeObject({});
}
}