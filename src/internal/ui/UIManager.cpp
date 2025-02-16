#include "UIManager.hpp"
#include "LoadManager.hpp"
#include "ui/widgets/Widget.hpp"

namespace summit::ui {
std::vector<std::string> UIManager::m_tabs = {};
std::map<std::string, std::map<std::string, widgets::Widget *>> UIManager::m_widgets = {};
std::map<std::string, std::vector<std::string>> UIManager::m_insertions = {};
std::vector<std::string> UIManager::getTabs() { return m_tabs; }
bool UIManager::registerTab(std::string tab) {
  if (std::find(m_tabs.begin(), m_tabs.end(), tab) != m_tabs.end()) {
    return false;
  }
  if (m_widgets.contains(tab) || m_insertions.contains(tab)) {
    return false;
  }
  m_widgets[tab] = {};
  m_insertions[tab] = {};
  m_tabs.push_back(tab);
  return true;
}

std::map<std::string, widgets::Widget *> UIManager::getWidgets(std::string tab) {
  return m_widgets.at(tab);
}
std::map<std::string, widgets::Widget *> UIManager::getWidgets() {
  std::map<std::string, widgets::Widget *> all = {};
  for (auto& [tab, widgets] : m_widgets) {
    for (auto& [id, widget] : widgets) {
      all[id] = widget;
    }
  }
  return all;
}

std::vector<std::string> UIManager::getInsertionOrder(std::string tab) {\
  return m_insertions[tab];
}

bool UIManager::registerWidget(std::string tab, widgets::Widget *widget) {
  if (!m_widgets.contains(tab) || !m_insertions.contains(tab)) {
    return false;
  }
  auto &wmap = m_widgets[tab];
  auto &wvec = m_insertions[tab];
  auto id = widget->getId();
  if (wmap.contains(id) || std::find(wvec.begin(), wvec.end(), id) != wvec.end()) { 
    return false;
  }
  wmap[id] = widget;
  wvec.push_back(id);
  return true;
}

$execute {
  LoadManager::onLoad([](){
    UIManager::registerTab("Global");
    UIManager::registerTab("Player");
    UIManager::registerTab("Config");
  },0,LoadTime::Early);
}

}
