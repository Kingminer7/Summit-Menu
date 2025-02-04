#include "LoadManager.hpp"
#include "Geode/loader/Event.hpp"
#include "Geode/loader/GameEvent.hpp"

namespace summit {

  LoadManager *LoadManager::instance = nullptr;

  void LoadManager::onLoad(std::function<void ()> func, int prio, LoadTime loadTime) {
    getCallbacks()->insert({prio, {func, loadTime}});
  }

  // so args can swap idrk
  void LoadManager::onLoad(std::function<void ()> func, LoadTime loadTime, int prio) {
    getCallbacks()->insert({prio, {func, loadTime}});
  }

  std::multimap<int, std::pair<std::function<void ()>, LoadTime>> *LoadManager::getCallbacks() {
    if (!instance) instance = new LoadManager;
    return &instance->callbacks;
  }

  $on_mod(Loaded) {
    for (const auto& [prio, callbackPair] : *LoadManager::getCallbacks()) {
      if (callbackPair.second == LoadTime::Early) {
        callbackPair.first();
      }
    }

    (new geode::EventListener<geode::GameEventFilter>(geode::GameEventType::Loaded))->bind([](geode::GameEvent* ev) {
      for (const auto& [prio, callbackPair] : *LoadManager::getCallbacks()) {
        if (callbackPair.second == LoadTime::MenuLayer) {
          callbackPair.first();
        }
      }
    });
  }
}