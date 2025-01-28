#include "Loader.hpp"
#include "Geode/loader/Event.hpp"
#include "Geode/loader/GameEvent.hpp"

namespace summit {

  std::multimap<int, std::pair<std::function<void ()>, LoadTime>> Loader::callbacks = {};

  void Loader::onLoad(std::function<void ()> func, int prio, LoadTime loadTime) {
    if (!func) return;
    callbacks.insert({prio, {func, loadTime}});
  }

  // so args can swap idrk
  void Loader::onLoad(std::function<void ()> func, LoadTime loadTime, int prio) {
    if (!func) return;
    callbacks.insert({prio, {func, loadTime}});
  }

  $on_mod(Loaded) {
    for (const auto& [prio, callbackPair] : Loader::callbacks) {
      if (callbackPair.second == LoadTime::Early) {
        callbackPair.first();
      }
    }

    (new geode::EventListener<geode::GameEventFilter>(geode::GameEventType::Loaded))->bind([](geode::GameEvent* ev) {
      for (const auto& [prio, callbackPair] : Loader::callbacks) {
        if (callbackPair.second == LoadTime::MenuLayer) {
          callbackPair.first();
        }
      }
    });
  }
}
