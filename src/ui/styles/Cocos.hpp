#pragma once

#include "Geode/cocos/menu_nodes/CCMenu.h"
#include "Geode/ui/Popup.hpp"
#include "Geode/ui/ScrollLayer.hpp"
#include "ui/Style.hpp"
#include <map>

namespace summit::ui::styles {
  class CocosUIStyle : public Style {
    public:
      virtual void init() override;
      virtual void deinit() override;

      virtual std::string getId() override;
      virtual StyleSystem getSystem() override;

      virtual void show() override;
      virtual void hide() override;

      void hideFromPopup();

      void update(float dt) override;
  };

  class CocosUI : public geode::Popup<CocosUIStyle *> {
    protected:
      bool m_closeHandled = false;
      bool setup(CocosUIStyle *style) override;
      CocosUIStyle *m_style = nullptr;
      geode::ScrollLayer *m_tabScroll;
      geode::ScrollLayer *m_hackScroll;
      std::map<std::string, cocos2d::CCMenu *> hackMenus = {};
    public:
      static CocosUI* create(CocosUIStyle *style);
      void onClose(CCObject *) override;
  };
}