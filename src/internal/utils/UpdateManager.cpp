#include "UpdateManager.hpp"
#include "Geode/loader/Log.hpp"

namespace summit {
  UpdateManager *UpdateManager::m_instance = nullptr;

  void UpdateManager::update(float dt) {
    for (auto cb : m_callbacks) {
      if (std::find(m_disabled.begin(), m_disabled.end(), cb.first) == m_disabled.end()) {
        cb.second(dt);
      }
    }
  }

  bool UpdateManager::init() {
    if (!CCNode::init()) return false;
    scheduleUpdate();
    onEnter();
    return true;
  }

  UpdateManager *UpdateManager::get() {
    if (!m_instance) m_instance = new UpdateManager;
    if (!m_instance->init()) {
      geode::log::error("Update manager failed to load... update will not be called!");
    }
    return m_instance;
  }
      
  void UpdateManager::registerUpdate(std::string id, std::function<void (float dt)> callback, bool enabled) {
    if (m_callbacks.contains(id))
      return geode::log::error("(UpdateManager) {} is already registered!", id);
    m_callbacks[id] = callback;
    if (!enabled)
      m_disabled.push_back(id);
  }
  void UpdateManager::removeUpdate(std::string id) {
    if (!m_callbacks.contains(id))
      return geode::log::error("(UpdateManager) {} is not registered!", id);
    m_callbacks.erase(id);
  }
  void UpdateManager::enableUpdate(std::string id) {
    if (m_callbacks.contains(id))
      return geode::log::error("(UpdateManager) {} is already registered!", id);
    if (std::find(m_disabled.begin(), m_disabled.end(), id) == m_disabled.end())
      return geode::log::error("(UpdateManager) {} is already enabled!", id);
    m_disabled.remove(id);
  }
  void UpdateManager::disableUpdate(std::string id) {
    if (m_callbacks.contains(id))
      return geode::log::error("(UpdateManager) {} is already registered!", id);
    if (std::find(m_disabled.begin(), m_disabled.end(), id) == m_disabled.end())
      return geode::log::error("(UpdateManager) {} is already enabled!", id);
    m_disabled.push_back(id);
  }
  std::map<std::string, std::function<void (float dt)>> UpdateManager::getCallbacks() {
    return m_callbacks;
  }
}