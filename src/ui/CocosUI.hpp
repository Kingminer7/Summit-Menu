#pragma once
#include <ui/styles/Style.hpp>
#include "ui/widgets/LabelWidget.hpp"

namespace summit::ui::styles {
class CocosUIPopup : public geode::Popup<> {
protected:
  bool setup() override {
    auto lw = summit::ui::widgets::LabelWidget::create(
                  "test", "Test Widget Really Long Because Im Doing Stuff "
                          "LolOloLolOlLoLLolOl");
    auto m = cocos2d::CCMenu::create();
    m->addChild(lw->createCocosNode());
    lw->setDescription("Test");
    m->addChild(lw->createCocosNode());
    lw->addSubWidget(lw);
    m->addChild(lw->createCocosNode());
    m->setLayout(geode::AxisLayout::create(geode::Axis::Column));
    m_mainLayer->addChild(m);
    return true;
  }

public:
  static CocosUIPopup *create() {
    auto ret = new CocosUIPopup();
    if (ret->initAnchored(240.f, 160.f)) {
      ret->autorelease();
      return ret;
    }

    delete ret;
    return nullptr;
  }
  void onClose(CCObject *sender) override;
};

class CocosUI : public Style {
protected:
  CocosUIPopup *popup;
  static CocosUI *instance;

public:
  void init() override { popup = CocosUIPopup::create(); }
  void deinit() override {
    if (popup)
      popup->removeMeAndCleanup();
  }
  void open() override {
    if (m_open) return;
    m_open = true;
    if (!popup)
      popup = CocosUIPopup::create();
    popup->show();
  }
  void close() override {
    if (!m_open) return;
    m_open = false;
    if (popup)
      popup->onExit();
  }
  StyleBase getStyleBase() override { return StyleBase::Cocos; }
  std::string getId() override { return "CocosUI"; }
  void update() override {}

  static CocosUI *getInstance() {
    if (!instance)
      instance = new CocosUI;
    return instance;
  }
};

CocosUI *CocosUI::instance = nullptr;

void CocosUIPopup::onClose(CCObject *sender) {
  Popup::onClose(sender);
  CocosUI::getInstance()->close();
}
} // namespace summit::ui::styles
