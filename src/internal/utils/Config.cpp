#include <Geode/Geode.hpp>
#include "LoadManager.hpp"

#include "Config.hpp"
namespace summit {
  matjson::Value Config::m_saved = nullptr;
  matjson::Value Config::m_temp = nullptr;

  bool Config::m_inited = false;

  void Config::init() {
    if (m_inited) return;
    auto mod = geode::Mod::get();
    m_saved = mod->getSavedValue<matjson::Value>("data", {});
    m_temp = {};
    m_inited = true;
  }

  void Config::save() {
    if (!m_inited) return;
    auto mod = geode::Mod::get();
    mod->setSavedValue<matjson::Value>("data", m_saved);
  }
}

$onLoad (Initial, -1000) {
  summit::Config::init();
}