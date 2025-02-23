#pragma once

#include <utils/LoadManager.hpp>
#include <map>
#include <string>
namespace summit::ui {
  enum class StyleSystem {
    ImGui,
    Cocos,
  };
  class Style {
    protected:
      bool m_visible = false;
    public:
      virtual void init() = 0;
      virtual void deinit() = 0;

      virtual std::string getId() = 0;
      virtual StyleSystem getSystem() = 0;

      virtual void show() = 0;
      virtual void hide();
      virtual void toggle() {
        if (m_visible) hide();
        else show();
      };
      virtual bool isVisible() {
        return m_visible;
      };

      // Called for whatever system is used **when the style is selected**
      // cocos uses CCObject::update, imgui uses draw, etc
      virtual void update(float dt) {}
  };

  class StyleManager {
    protected:
      static StyleManager *m_instance;
      std::map<std::string, Style*> m_styles = {};

      Style *m_currentStyle = nullptr;
    public:
      static StyleManager *get();

      void registerStyle(Style *style);
      void unregisterStyle(std::string id);
      Style *getStyle(std::string id);
      std::map<std::string, Style*> getStyles();

      Style *getCurrentStyle();
      std::string getCurrentId();
      void setCurrentStyle(std::string id);
  };

  #define RegisterStyle(T) $onLoad(Initial, 0) { \
    StyleManager::get()->registerStyle(new T); \
  }
}