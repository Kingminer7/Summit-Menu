#include "LabelWidget.hpp"

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

    auto bg = extension::CCScale9Sprite::create("GJ_square05.png");
    bg->setContentSize(csize);
    node->addChildAtPosition(bg, geode::Anchor::Center);
    
    auto lab = CCLabelBMFont::create(label.c_str(), "chatFont.fnt");
    auto lWidth = csize.width - 5.f;
    if (!desc.empty()) {
      lWidth -= 15.f;
    }
    if (!subWidgets.empty()) {
      lWidth -= 20.f;
    }
    lab->limitLabelWidth(lWidth,2.f, .1f);
    lab->setContentSize({lWidth, csize.height - 5.f});
    node->addChildAtPosition(lab, geode::Anchor::Left, {5.f, 0.f});
    lab->setAnchorPoint({0.f, .5f});

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
}