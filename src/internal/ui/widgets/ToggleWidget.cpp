#include "ToggleWidget.hpp"
#include "Geode/binding/CCMenuItemToggler.hpp"
#include "Geode/cocos/cocoa/CCObject.h"
#include "ui/UIManager.hpp"

using namespace cocos2d;

namespace summit::ui::widgets {
  std::string ToggleWidget::getType() {
    return "Toggle";
  }

  ToggleWidget *ToggleWidget::setLabel(std::string label) {
    this->label = label;
    return this;
  }

  ToggleWidget *ToggleWidget::setDescription(std::string desc) {
    this->desc = desc;
    return this;
  }

  ToggleWidget *ToggleWidget::setSize(WidgetSize size) {
    this->size = size;
    return this;
  }
  
  ToggleWidget *ToggleWidget::addSubWidget(Widget *widget) {
    if (widget) {
      subWidgets[widget->getId()] = widget;
    }
    return this;
  }

  CCNode *ToggleWidget::createCocosNode() {
    auto csize = getCCSize(size);
    auto node = CCNode::create();
    node->setContentSize(csize);
    node->setID(fmt::format("{}-{}", getType(), getId()));
    
    auto lab = CCLabelBMFont::create(label.c_str(), "bigFont.fnt");
    lab->setAnchorPoint({0.f, .5f});
    auto lWidth = csize.width - 45.f;
    CCMenu *menu = CCMenu::create();
    menu->setContentSize(node->getContentSize());
    node->addChildAtPosition(menu, geode::Anchor::Center);
    if (!desc.empty()) {
      lWidth -= 15.f;
      auto descSpr = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
      descSpr->setScale(12.5 / descSpr->getContentHeight());
      auto descBtn = CCMenuItemSpriteExtra::create(
          descSpr, node, menu_selector(ToggleWidget::onInfoCC)
      );
      menu->addChildAtPosition(descBtn, geode::Anchor::Left, {12.5f + lWidth, 0});
    }
    if (!subWidgets.empty()) {
      lWidth -= 20.f;
    }

    auto toggle = CCMenuItemToggler::createWithStandardSprites(node, menu_selector(ToggleWidget::onToggle), .75f);
    toggle->toggle(value);
    menu->addChildAtPosition(toggle, geode::Anchor::Left, {lWidth + 20.f, 0.f});

    lab->limitLabelWidth(lWidth,.5f, .05f);
    node->addChildAtPosition(lab, geode::Anchor::Left, {5.f, 0.f});

    return node;
  }

  void ToggleWidget::renderImGui() {

  }

  void ToggleWidget::init(std::string id, std::string label, bool default_, std::function<void (bool value)> callback) {
    this->id = id;
    this->label = label;
    this->value = default_;
    this->callback = callback;
  }

  ToggleWidget *ToggleWidget::create(std::string id, std::string label, bool default_, std::function<void (bool value)> callback) {
    auto widget = new ToggleWidget;
    widget->init(id, label, default_, callback);
    return widget;
  }

  bool ToggleWidget::getValue() {
    return value;
  }

  ToggleWidget *ToggleWidget::setValue(bool value) {
    this->value = value;
    return this;
  }

  std::function<void (bool value)> ToggleWidget::getCallback() {
    return callback;
  }

  ToggleWidget *ToggleWidget::setCallback(std::function<void (bool value)> callback) {
    this->callback = callback;
    return this;
  }

  void ToggleWidget::onToggle(CCObject *sender) {
    if (!sender) return;
    if (auto toggler = geode::cast::typeinfo_cast<CCMenuItemToggler *>(sender)) {
      auto widgets = UIManager::getWidgets();
      if (widgets.find(toggler->getParent()->getParent()->getID()) == widgets.end()) return;
      if (auto w = widgets.at(toggler->getParent()->getParent()->getID())) {
        if (auto toggle = static_cast<ToggleWidget *>(w)) {
          if (toggle->callback) toggle->callback(toggler->isToggled());
        }
      }
    }
  }
}