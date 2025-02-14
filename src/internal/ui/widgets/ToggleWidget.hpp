#pragma once

#include "Widget.hpp"

namespace summit::ui::widgets {
  class ToggleWidget : public Widget {
    protected:
      void init(std::string id, std::string label, bool default_, std::function<void (bool value)> callback);
      bool value;
      std::function<void (bool value)> callback;
    public:
      void renderImGui() override;
      cocos2d::CCNode *createCocosNode() override;
      std::string getType() override;
      ToggleWidget *setLabel(std::string label);
      ToggleWidget *setDescription(std::string desc);
      ToggleWidget *addSubWidget(Widget *widget);
      ToggleWidget *setSize(WidgetSize size);
      std::function<void (bool value)> getCallback();
      ToggleWidget *setCallback(std::function<void (bool value)> callback);
      ToggleWidget *setValue(bool value);
      bool getValue();

      void onToggle(cocos2d::CCObject *sender);

      static ToggleWidget *create(std::string id, std::string label, bool default_, std::function<void (bool value)> callback);
  };
}