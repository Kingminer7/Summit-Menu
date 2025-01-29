#include "Loader.hpp"
#include "Geode/loader/Event.hpp"
#include "Geode/loader/GameEvent.hpp"

namespace summit {

  Loader *Loader::instance = nullptr;

  void Loader::onLoad(std::function<void ()> func, int prio, LoadTime loadTime) {
    getCallbacks()->insert({prio, {func, loadTime}});
  }

  // so args can swap idrk
  void Loader::onLoad(std::function<void ()> func, LoadTime loadTime, int prio) {
    getCallbacks()->insert({prio, {func, loadTime}});
  }

  std::multimap<int, std::pair<std::function<void ()>, LoadTime>> *Loader::getCallbacks() {
    if (!instance) instance = new Loader;
    return &instance->callbacks;
  }

  $on_mod(Loaded) {
    for (const auto& [prio, callbackPair] : *Loader::getCallbacks()) {
      if (callbackPair.second == LoadTime::Early) {
        callbackPair.first();
      }
    }

    (new geode::EventListener<geode::GameEventFilter>(geode::GameEventType::Loaded))->bind([](geode::GameEvent* ev) {
      for (const auto& [prio, callbackPair] : *Loader::getCallbacks()) {
        if (callbackPair.second == LoadTime::MenuLayer) {
          callbackPair.first();
        }
      }
    });
  }
}