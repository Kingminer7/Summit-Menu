#include "Hack.hpp"
#include "Geode/loader/Log.hpp"

namespace summit::hacks {
  HackManager *HackManager::m_instance = nullptr;

  HackManager *HackManager::get() {
    if (!m_instance) m_instance = new HackManager;
    return m_instance;
  }

  void HackManager::registerHack(Hack *hack) {
    if (!hack) return geode::log::error("(HackManager) No hack provided.");
    auto id = hack->getId();
    if (m_hacks.contains(id))  return geode::log::error("(HackManager) Hack {} already registered.", id);
    m_hacks[id] = hack;
  }

  Hack *HackManager::getHack(std::string id) {
    return m_hacks[id];
  }

  std::map<std::string, Hack*> HackManager::getHacks() {
    return m_hacks;
  }

  $onLoad(Initial, 20) {
    for (auto hack : HackManager::get()->getHacks()) {
      hack.second->init();
    }
  }
}