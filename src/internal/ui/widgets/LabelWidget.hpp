#pragma once

#include "Widget.hpp"

namespace summit::ui::widgets {
  class LabelWidget : public Widget {
    protected:
      cocos2d::CCPoint align = {0, 0.5};
      void init(std::string id, std::string label);
    public:
      void renderImGui() override;
      cocos2d::CCNode *createCocosNode() override;
      std::string getType() override;
      LabelWidget *setLabel(std::string label);
      LabelWidget *setDescription(std::string desc);
      LabelWidget *addSubWidget(Widget *widget);
      LabelWidget *setSize(WidgetSize size);
      LabelWidget *setAlignment(cocos2d::CCPoint align);
      cocos2d::CCPoint getAlignment();

      static LabelWidget *create(std::string id, std::string label);
  };
}