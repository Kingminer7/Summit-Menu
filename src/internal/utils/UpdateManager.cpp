#include "UpdateManager.hpp"
#include "Geode/loader/Log.hpp"

namespace summit {
  UpdateManager *UpdateManager::instance = nullptr;

  bool UpdateManager::init() {
    if (!CCNode::init()) return false;
    scheduleUpdate();
    return true;
  }

  void UpdateManager::update(float dt) {
    for (auto cb : callbacks) {
      if (std::find(disabled.begin(), disabled.end(), cb.first) == disabled.end()) {
        cb.second(dt);
      }
    }
  }

  UpdateManager *UpdateManager::get() {
    if (!instance) instance = new UpdateManager;
    instance->init();
    return instance;
  }
      
  void UpdateManager::registerUpdate(std::string id, std::function<void (float dt)> callback) {
    if (callbacks.contains(id))
      return geode::log::error("(UpdateManager) {} is already registered!", id);
    callbacks[id] = callback;
  }
  void UpdateManager::removeUpdate(std::string id) {
    if (!callbacks.contains(id))
      return geode::log::error("(UpdateManager) {} is not registered!", id);
    callbacks.erase(id);
  }
  void UpdateManager::enableUpdate(std::string id) {
    if (callbacks.contains(id))
      return geode::log::error("(UpdateManager) {} is already registered!", id);
    if (std::find(disabled.begin(), disabled.end(), id) == disabled.end())
      return geode::log::error("(UpdateManager) {} is already enabled!", id);
    disabled.remove(id);
  }
  void UpdateManager::disableUpdate(std::string id) {
    if (callbacks.contains(id))
      return geode::log::error("(UpdateManager) {} is already registered!", id);
    if (std::find(disabled.begin(), disabled.end(), id) == disabled.end())
      return geode::log::error("(UpdateManager) {} is already enabled!", id);
    disabled.push_back(id);
  }
  std::map<std::string, std::function<void (float dt)>> UpdateManager::getCallbacks() {
    return callbacks;
  }
}