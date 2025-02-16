#include "ToggleWidget.hpp"

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

  CCNode *ToggleWidget::createNode() {
    return cocos::ToggleNode::create(this);
  }

  void ToggleWidget::renderImGui() {

  }

  void ToggleWidget::init(std::string id, std::string label, bool default_) {
    this->id = id;
    this->label = label;
    this->toggled = default_;
  }

  ToggleWidget *ToggleWidget::create(std::string id, std::string label, bool default_) {
    auto widget = new ToggleWidget;
    widget->init(id, label, default_);
    return widget;
  }

  ToggleWidget *ToggleWidget::setAlignment(CCPoint align) {
    this->align = align;
    return this;
  }

  CCPoint ToggleWidget::getAlignment() {
    return this->align;
  }

  ToggleWidget *ToggleWidget::toggle() {
    toggled = !toggled;
    return this;
  }

  ToggleWidget *ToggleWidget::toggle(bool toggled) {
    this->toggled = toggled;
    return this;
  }

  ToggleWidget *ToggleWidget::setCallback(std::function<void (bool toggled)> callback) {
    this->callback = callback;
    return this;
  }
  std::function<void (bool toggled)> ToggleWidget::getCallback() {
    return callback;
  }

  namespace cocos {
    bool ToggleNode::init(ToggleWidget *widget) {
      if (!CCNode::init()) return false;
      this->m_widget = widget;
      auto size = getCCSize(widget->getSize());
      auto type = widget->getType();
      auto id = widget->getId();
      auto desc = widget->getDescription();
      auto align = widget->getAlignment();

      setContentSize(size);
      setID(fmt::format("{}-{}", type, id));
      
      m_buttonMenu = CCMenu::create();
      m_buttonMenu->setContentSize(size);
      addChildAtPosition(m_buttonMenu, geode::Anchor::Center);

      auto lWidth = size.width - 10.f;
      if (!desc.empty()) {
        lWidth -= 15.f;
        auto descSpr = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
        descSpr->setScale(12.5 / descSpr->getContentHeight());
        auto descBtn = CCMenuItemSpriteExtra::create(
            descSpr, this, menu_selector(ToggleNode::onInfo)
        );
        m_buttonMenu->addChildAtPosition(descBtn, geode::Anchor::Left, {12.5f + lWidth, 0});
      }

      if (!widget->getSubWidgets().empty()) {
        lWidth -= 26.75f;
        auto subSpr = CCSprite::createWithSpriteFrameName("accountBtn_settings_001.png");
        subSpr->setScale(22.5 / subSpr->getContentHeight());
        auto descBtn = CCMenuItemSpriteExtra::create(
            subSpr, this, menu_selector(ToggleNode::onSubWidgets)
        );
        m_buttonMenu->addChildAtPosition(descBtn, geode::Anchor::Left, {18.35f + lWidth, 0});
      }

      auto toggle = CCMenuItemToggler::createWithStandardSprites(this, menu_selector(ToggleNode::onToggle), .75f);
      m_buttonMenu->addChildAtPosition(toggle, geode::Anchor::Left, {lWidth, 0});
      lWidth -= 20;

      m_label = CCLabelBMFont::create(widget->getLabel().c_str(), "bigFont.fnt");
      m_label->setAnchorPoint(align);
      m_label->limitLabelWidth(lWidth,.5f, .05f);
      addChildAtPosition(m_label, geode::Anchor::Left, {5.f + lWidth * (align.x), 0.f});

      return true;
    }

    ToggleNode *ToggleNode::create(ToggleWidget *widget) {
      auto ret = new ToggleNode();
      if (ret->init(widget)) {
        ret->autorelease();
        return ret;
      }

      delete ret;
      return nullptr;
    }

    ToggleWidget *ToggleNode::getWidget() {
      return m_widget;
    }

    void ToggleNode::onInfo(CCObject *sender) {
      FLAlertLayer::create(m_widget->getLabel().c_str(), m_widget->getDescription(), "Close")->show();
    }

    void ToggleNode::onSubWidgets(CCObject *sender) {
      FLAlertLayer::create("Not implemented", "Sub widget popup not implemented.", "Ok")->show();
    }

    void ToggleNode::onToggle(CCObject *sender) {
      m_widget->toggle();
    }
  }
}