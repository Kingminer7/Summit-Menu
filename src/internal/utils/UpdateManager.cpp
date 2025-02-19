#include "UpdateManager.hpp"
#include "Geode/loader/Log.hpp"

namespace summit {
  UpdateManager *UpdateManager::instance = nullptr;

  bool UpdateManager::init() {
    if (!CCNode::init()) return false;
    scheduleUpdate();
    return true;
  }

  // void UpdateManager::update(float dt) {
  //   for (auto cb : callbacks) {
  //     if (std::find(disabled.begin(), disabled.end(), cb.first) == disabled.end()) {
        
  //     }
  //   }
  // }

  // UpdateManager *UpdateManager::get() {
  //   if (!instance) instance = new UpdateManager;
  //   instance->init();
  //   return instance;
  // }
      
  // void UpdateManager::registerUpdate(std::string id, cocos2d::SEL_MenuHandler callback) {
  //   if (callbacks.contains(id))
  //     return geode::log::error("(UpdateManager) {} is already registered!", id);
  //   callbacks[id] = callback;
  // }
  // void UpdateManager::removeUpdate(std::string id);
  // void UpdateManager::enableUpdate(std::string id);
  // void UpdateManager::disableUpdate(std::string id);
  // std::map<std::string, cocos2d::SEL_MenuHandler> UpdateManager::getCallbacks();
}