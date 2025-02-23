#include "UIManager.hpp"
#include "Geode/loader/Log.hpp"
#include <utils/LoadManager.hpp>

namespace summit::ui {
  UIManager *UIManager::m_instance = nullptr;

  UIManager *UIManager::get() {
    if (!m_instance) m_instance = new UIManager;
    return m_instance;
  }

  void UIManager::registerTab(Tab *tab) {
    if (!tab) geode::log::error("(UIManager) No tab provided.");
    auto id = tab->getId();
    if (m_tabs.contains(id)) return geode::log::error("(UIManager) Tab {} already registered.", id);
    m_tabs[id] = tab;
    m_order.push_back(id);
  }
  
  Tab *UIManager::getTab(std::string id) {
    return m_tabs[id];
  }
  
  std::map<std::string, Tab *> UIManager::getTabs() {
    return m_tabs;
  }

  std::list<std::string> UIManager::getOrder() {
    return m_order;
  }

  // Tab

  void Tab::init(std::string id) {
    this->m_id = id;
  }

  std::string Tab::getId() {
    return m_id;
  }

  Tab *Tab::create(std::string id) {
    auto ret = new Tab;
    ret->init(id);
    return ret;
  }

  std::map<std::string, Widget *> Tab::getWidgets() {
    return m_widgets;
  }

  Widget *Tab::getWidget(std::string id) {
    return m_widgets[id];
  }

  void Tab::addWidget(Widget *widget) {
    if (!widget) geode::log::error("(Tab {}) No widget provided.", m_id);
    auto id = widget->getId();
    if (m_widgets.contains(id)) return geode::log::error("(Tab {}) Widget {} already registered.", m_id, id);
    m_order.push_back(id);
    m_widgets[id] = widget;
  }

  void Tab::removeWidget(std::string id) {
    if (!m_widgets.contains(id)) return geode::log::error("(Tab {}) Widget {} not registered.", m_id, id);
    m_widgets.erase(id);
    m_order.remove(id);
  }

  std::list<std::string> Tab::getOrder() {
    return m_order;
  }

  // Widget

  void Widget::init(std::string id, std::string label) {
    this->m_id = id;
    this->m_label = label;
  }

  std::string Widget::getId() {
    return m_id;
  }
  
  auto *Widget::setLabel(std::string label) {
    this->m_label = label;
    return this;
  }

  Widget *Widget::create(std::string id, std::string label) {
    auto ret = new Widget;
    ret->init(id, label);
    return ret;
  }

  $onLoad(Initial, 0)  {
    UIManager::get()->registerTab(Tab::create("Global"));
    UIManager::get()->registerTab(Tab::create("Player"));
    UIManager::get()->registerTab(Tab::create("Config"));
  }
}