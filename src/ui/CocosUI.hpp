#pragma once
#include <ui/styles/Style.hpp>

namespace summit::ui::styles {

class CocosUI : public Style {
public:
  class UIPopup;

protected:
  static CocosUI *m_instance;
  UIPopup *m_popup = nullptr;

public:
  void init() override;
  void deinit() override;
  void open() override;
  void close() override;
  StyleBase getStyleBase() override;
  std::string getId() override;
  void update() override;

  static CocosUI *getInstance();
};

class CocosUI::UIPopup : public geode::Popup<> {
protected:
  std::string currentTab = "Global";
  geode::ScrollLayer *tabScroll;
  std::map<std::string, geode::ScrollLayer *> hackScrolls;
  bool setup() override;
public:
  static UIPopup *create();
  void onClose(CCObject * sender) override;
  void onTab(CCObject * tab);
};

}