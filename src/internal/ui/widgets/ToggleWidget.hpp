#pragma once

#include "Widget.hpp"

namespace summit::ui::widgets {
  class ToggleWidget : public Widget {
    protected:
      cocos2d::CCPoint align = {0, 0.5};
      void init(std::string id, std::string label, bool default_);
      bool toggled;
      std::function<void (bool toggled)> callback;
    public:
      void renderImGui() override;
      cocos2d::CCNode *createNode() override;
      std::string getType() override;
      ToggleWidget *setLabel(std::string label);
      ToggleWidget *setDescription(std::string desc);
      ToggleWidget *addSubWidget(Widget *widget);
      ToggleWidget *setSize(WidgetSize size);
      ToggleWidget *setAlignment(cocos2d::CCPoint align);
      cocos2d::CCPoint getAlignment();
      bool isToggled();
      ToggleWidget *toggle();
      ToggleWidget *toggle(bool toggle);
      ToggleWidget *setCallback(std::function<void (bool toggled)> callback);
      std::function<void (bool toggled)> getCallback();

      static ToggleWidget *create(std::string id, std::string label, bool default_);
  };
  namespace cocos {
    class ToggleNode : public cocos2d::CCNode {
      protected:
        ToggleWidget *m_widget = nullptr;
        cocos2d::CCMenu *m_buttonMenu = nullptr;
        cocos2d::CCLabelBMFont *m_label = nullptr;
      public:
        bool init(ToggleWidget *widget);
        static ToggleNode *create(ToggleWidget *widget);
        ToggleWidget *getWidget();
        cocos2d::CCLabelBMFont* getLabel();
        cocos2d::CCMenu* getMenu();

        void onInfo(cocos2d::CCObject *sender);
        void onSubWidgets(cocos2d::CCObject *sender);
        void onToggle(CCObject *sender);
    };
  }
}