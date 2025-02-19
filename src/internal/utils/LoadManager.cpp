#include "LoadManager.hpp"
#include "Geode/loader/GameEvent.hpp"
#include "Geode/loader/ModEvent.hpp"

namespace summit {
  LoadManager *LoadManager::m_instance = nullptr;

  LoadManager *LoadManager::get() {
    if (!m_instance) m_instance = new LoadManager;
    return m_instance;
  }
  
  void LoadManager::onLoad(std::function<void ()> function, LoadManager::LoadType loadType, int prio) {
    if (!function) return;
    m_callbacks.insert({prio, {function, loadType}});
  }

  std::multimap<int, std::pair<std::function<void ()>, LoadManager::LoadType>> LoadManager::getCallbacks() {
    return m_callbacks;
  }
  
}

$on_mod(Loaded) {
  auto cb = summit::LoadManager::get()->getCallbacks();
  for (auto lc : cb) {
    if (lc.second.second == summit::LoadManager::LoadType::Initial) {
      lc.second.first();
    }
  }
  (new geode::EventListener<geode::GameEventFilter>(geode::GameEventType::Loaded))->bind([](geode::GameEvent* ev) {
    for (auto lc : summit::LoadManager::get()->getCallbacks()) {
      if (lc.second.second == summit::LoadManager::LoadType::MenuLayer) {
        lc.second.first();
      }
    }
  });
}