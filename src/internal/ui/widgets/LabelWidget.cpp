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

  CCNode *LabelWidget::createCocosNode() {
    auto csize = getCCSize(size);
    auto node = CCNode::create();
    node->setContentSize(csize);
    node->setID(fmt::format("{}-{}", getType(), getId()));
    CCMenu *menu = CCMenu::create();
    menu->setContentSize(node->getContentSize());
    node->addChildAtPosition(menu, geode::Anchor::Center);
    
    auto lab = CCLabelBMFont::create(label.c_str(), "bigFont.fnt");
    lab->setAnchorPoint(align);
    auto lWidth = csize.width - 10.f;
    if (!desc.empty()) {
      lWidth -= 15.f;
      auto descSpr = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
      descSpr->setScale(12.5 / descSpr->getContentHeight());
      auto descBtn = CCMenuItemSpriteExtra::create(
          descSpr, node, menu_selector(LabelWidget::onInfoCC)
      );
      menu->addChildAtPosition(descBtn, geode::Anchor::Left, {12.5f + lWidth, 0});
    }
    if (!subWidgets.empty()) {
      lWidth -= 20.f;
    }
    lab->limitLabelWidth(lWidth,.5f, .05f);
    node->addChildAtPosition(lab, geode::Anchor::Left, {5.f + lWidth * (align.x), 0.f});

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
}