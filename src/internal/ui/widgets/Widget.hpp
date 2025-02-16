#pragma once

#include <Geode/Geode.hpp>

namespace summit::ui::widgets {
enum class WidgetSize {
  Half, // Half width, normal height
  Full, // Full width, normal height
  // womp womp
  // HalfDouble, // Half width, double height
  // FullDouble, // Full width, double height
};
cocos2d::CCSize getCCSize(WidgetSize size);

class Widget {
protected:
  std::string label;
  std::string id;
  std::string desc;
  std::map<std::string, Widget *> subWidgets = {};
  WidgetSize size = WidgetSize::Half;
public:
  virtual void renderImGui() = 0;
  virtual cocos2d::CCNode *createNode() = 0;
  virtual std::string getType() = 0;
  std::string getId();
  std::string getLabel();
  std::string getDescription();
  WidgetSize getSize();
  std::map<std::string, Widget *> getSubWidgets();
};
}