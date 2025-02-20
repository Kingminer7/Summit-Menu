#pragma once

#include "Geode/ui/Popup.hpp"
#include "ui/Style.hpp"

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
    public:
      static CocosUI* create(CocosUIStyle *style);
      void onClose(CCObject *) override;
      void removeFromParent() override;
  };
}