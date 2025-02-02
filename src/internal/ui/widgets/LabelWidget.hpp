#pragma once

#include "Widget.hpp"

namespace summit::ui::widgets {
  class LabelWidget : public Widget {
    public:
      void renderImGui() override;
      cocos2d::CCNode *createCocosNode() override;
      std::string getType() override;
      void init(std::string id, std::string label);
      LabelWidget *setLabel(std::string label);
      LabelWidget *setDescription(std::string desc);
      LabelWidget *addSubWidget(Widget *widget);
      LabelWidget *setSize(WidgetSize size);

      static LabelWidget *create(std::string id, std::string label);
  };
}