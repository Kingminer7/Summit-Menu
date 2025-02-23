#include "ui/Style.hpp"
#include "Geode/loader/Log.hpp"
#include "utils/Config.hpp"
#include "utils/UpdateManager.hpp"
#include <fmt/format.h>
namespace summit::ui {
  StyleManager *StyleManager::m_instance = nullptr;

  StyleManager *StyleManager::get() {
    if (!m_instance) m_instance = new StyleManager;
    return m_instance;
  }

  void StyleManager::registerStyle(Style *style) {
    if (!style)
      return geode::log::error("(StyleManager) A style was registered but did not exist.");
    if (m_styles.contains(style->getId()))
      return geode::log::error("(StyleManager) {} is already registered!", style->getId());
    m_styles[style->getId()] = style;
    if (style->getSystem() == StyleSystem::Cocos) {
      UpdateManager::get()->registerUpdate(fmt::format("style-{}", style->getId()), [style](float dt) { style->update(dt); }, false);
    }
  }
  void StyleManager::unregisterStyle(std::string id) {
    if (!m_styles.contains(id))
      return geode::log::error("(StyleManager) {} is not registered!", id);
    m_styles.erase(id);
  }
  Style *StyleManager::getStyle(std::string id) {
    return m_styles[id];
  }
  std::map<std::string, Style*> StyleManager::getStyles() {
    return m_styles;
  }

  Style *StyleManager::getCurrentStyle() {
    return m_currentStyle;
  }

  std::string StyleManager::getCurrentId() {
    return m_currentStyle ? m_currentStyle->getId() : "";
  }

  void StyleManager::setCurrentStyle(std::string id) {
    if (m_styles.contains(id)) {
      if (m_currentStyle) m_currentStyle->deinit();
      m_currentStyle = m_styles[id];
      m_currentStyle->init();
    }
  }

  void Style::hide() {
    Config::save();
  }

  $onLoad(Initial, 5) {
    StyleManager::get()->setCurrentStyle("CocosUI");
  }
}