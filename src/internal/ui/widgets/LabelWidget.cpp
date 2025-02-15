#include "LabelWidget.hpp"
#include "Geode/ui/Layout.hpp"

using namespace cocos2d;

namespace summit::ui::widgets {
  std::string LabelWidget::getType() {
    return "Label";
  }

  LabelWidget *LabelWidget::setLabel(std::string label) {
    this->label = label;
    return this;
  }

  LabelWidget *LabelWidget::setDescription(std::string desc) {
    this->desc = desc;
    return this;
  }

  LabelWidget *LabelWidget::setSize(WidgetSize size) {
    this->size = size;
    return this;
  }
  
  LabelWidget *LabelWidget::addSubWidget(Widget *widget) {
    if (widget) {
      subWidgets[widget->getId()] = widget;
    }
    return this;
  }

  CCNode *LabelWidget::getCocosNode() {
    if (!node) node = cocos::LabelNode::create(this);
    return node;
  }

  void LabelWidget::renderImGui() {

  }

  void LabelWidget::init(std::string id, std::string label) {
    this->id = id;
    this->label = label;
  }

  LabelWidget *LabelWidget::create(std::string id, std::string label) {
    auto widget = new LabelWidget;
    widget->init(id, label);
    return widget;
  }

  LabelWidget *LabelWidget::setAlignment(CCPoint align) {
    this->align = align;
    return this;
  }

  CCPoint LabelWidget::getAlignment() {
    return this->align;
  }

  namespace cocos {
    bool LabelNode::init(LabelWidget *widget) {
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
            descSpr, this, menu_selector(LabelNode::onInfo)
        );
        m_buttonMenu->addChildAtPosition(descBtn, geode::Anchor::Left, {12.5f + lWidth, 0});
      }

      if (!widget->getSubWidgets().empty()) {
        lWidth -= 26.75f;
        auto subSpr = CCSprite::createWithSpriteFrameName("accountBtn_settings_001.png");
        subSpr->setScale(22.5 / subSpr->getContentHeight());
        auto descBtn = CCMenuItemSpriteExtra::create(
            subSpr, this, menu_selector(LabelNode::onSubWidgets)
        );
        m_buttonMenu->addChildAtPosition(descBtn, geode::Anchor::Left, {18.35f + lWidth, 0});
      }

      m_label = CCLabelBMFont::create(widget->getLabel().c_str(), "bigFont.fnt");
      m_label->setAnchorPoint(align);
      m_label->limitLabelWidth(lWidth,.5f, .05f);
      addChildAtPosition(m_label, geode::Anchor::Left, {5.f + lWidth * (align.x), 0.f});

      return true;
    }

    LabelNode *LabelNode::create(LabelWidget *widget) {
      auto ret = new LabelNode();
      if (ret->init(widget)) {
        ret->autorelease();
        return ret;
      }

      delete ret;
      return nullptr;
    }

    LabelWidget *LabelNode::getWidget() {
      return m_widget;
    }

    void LabelNode::onInfo(CCObject *sender) {
      FLAlertLayer::create("Not implemented", "Info popup not implemented.", "Ok")->show();
    }

    void LabelNode::onSubWidgets(CCObject *sender) {
      FLAlertLayer::create("Not implemented", "Sub widget popup not implemented.", "Ok")->show();
    }
  }
}