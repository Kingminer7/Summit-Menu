#pragma once

#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include "Geode/cocos/menu_nodes/CCMenu.h"
#include "Widget.hpp"

namespace summit::ui::widgets {
  class LabelWidget : public Widget {
    protected:
      cocos2d::CCPoint align = {0, 0.5};
      void init(std::string id, std::string label);
    public:
      void renderImGui() override;
      cocos2d::CCNode *createNode() override;
      std::string getType() override;
      LabelWidget *setLabel(std::string label);
      LabelWidget *setDescription(std::string desc);
      LabelWidget *addSubWidget(Widget *widget);
      LabelWidget *setSize(WidgetSize size);
      LabelWidget *setAlignment(cocos2d::CCPoint align);
      cocos2d::CCPoint getAlignment();

      static LabelWidget *create(std::string id, std::string label);
  };
  namespace cocos {
    class LabelNode : public cocos2d::CCNode {
      protected:
        LabelWidget *m_widget = nullptr;
        cocos2d::CCMenu *m_buttonMenu = nullptr;
        cocos2d::CCLabelBMFont *m_label = nullptr;
      public:
        bool init(LabelWidget *widget);
        static LabelNode *create(LabelWidget *widget);
        LabelWidget *getWidget();
        cocos2d::CCLabelBMFont* getLabel();
        cocos2d::CCMenu* getMenu();

        // @brief Cocos ui
        void onInfo(cocos2d::CCObject *sender);
        // @brief Cocos ui
        void onSubWidgets(cocos2d::CCObject *sender);
    };
  }
}