#include "UIManager.hpp"

namespace summit::ui {
std::vector<std::string> UIManager::m_tabs = {
    "Global",
    "Player",
    "Level",
    "Settings",
};
std::vector<std::string> UIManager::getTabs() { return m_tabs; }
bool UIManager::registerTab(std::string tab) {
  if (std::find(m_tabs.begin(), m_tabs.end(), tab) != m_tabs.end()) {
    return false;
  }
  m_tabs.push_back(tab);
  return true;
}
}