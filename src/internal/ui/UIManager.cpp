#include "UIManager.hpp"
#include "LoadManager.hpp"
#include "ui/widgets/LabelWidget.hpp"
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
  if (m_widgets.contains(tab)) {
    return false;
  }
  m_widgets[tab] = {};
  m_tabs.push_back(tab);
  return true;
}

std::map<std::string, widgets::Widget *> UIManager::getWidgets(std::string tab) {
  return m_widgets.at(tab);
}
std::map<std::string, widgets::Widget *> UIManager::getWidgets() {
  std::map<std::string, widgets::Widget *> all;
  for (auto& [tab, widgets] : m_widgets) {
    for (auto& [id, widget] : widgets) {
      all[id] = widget;
    }
  }
  return all;
}

std::vector<std::string> UIManager::getInsertionOrder(std::string tab) {
  return m_insertions[tab];
}

bool UIManager::registerWidget(std::string tab, widgets::Widget *widget) {
  if (m_widgets.find(tab) == m_widgets.end()) {
    return false;
  }
  auto &wmap = m_widgets[tab];
  auto id = widget->getId();
  if (wmap.find(id) != wmap.end()) { 
    return false;
  }
  wmap[id] = widget;
  return true;
}

$execute {
  LoadManager::onLoad([](){
    UIManager::registerTab("Global");
    UIManager::registerTab("Player");
    // #ifdef DEBUG_BUILD
    UIManager::registerTab("Debug");
    {
      auto w = widgets::LabelWidget::create("debug.label-half", "Test Half Label")->setSize(widgets::WidgetSize::Half);
      UIManager::registerWidget("Debug", w);
    }
    {
      auto w = widgets::LabelWidget::create("debug.label-full", "Test Full Label")->setSize(widgets::WidgetSize::Full);
      UIManager::registerWidget("Debug", w);
    }
    {
      auto w = widgets::LabelWidget::create("debug.label-doublefull", "Test Double Full Label")->setSize(widgets::WidgetSize::FullDouble);
      UIManager::registerWidget("Debug", w);
    }
    {
      auto w = widgets::LabelWidget::create("debug.label-doublehalf", "Test Double Half Label")->setSize(widgets::WidgetSize::HalfDouble);
      UIManager::registerWidget("Debug", w);
    }
    // #endif
    UIManager::registerTab("Config");
  },0,LoadTime::Early);
}

}
