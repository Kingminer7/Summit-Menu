#include "Widget.hpp"

using namespace cocos2d;

namespace summit::ui::widgets {
  std::map<WidgetSize, CCSize> sizes = {
    {WidgetSize::Half, {150.f, 30.f}},
    {WidgetSize::Full, {300.f, 30.f}},
    {WidgetSize::HalfDouble, {150.f, 60.f}},
    {WidgetSize::FullDouble, {300.f, 60.f}}
  };
  CCSize getCCSize(WidgetSize size) {
    return sizes[size];
  }

  std::string Widget::getId() {
    return id;
  }

  std::string Widget::getLabel() {
    return label;
  }

  std::string Widget::getDescription() {
    return desc;
  }

  std::map<std::string, Widget *> Widget::getSubWidgets() {
    return subWidgets;
  }
}