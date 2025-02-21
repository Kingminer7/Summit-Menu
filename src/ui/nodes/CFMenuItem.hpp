#pragma once

#include "Geode/binding/CCMenuItemSpriteExtra.hpp"

// Because rob hardcoded color. I hate that I had to do this.

namespace summit::ui {
  class CFMenuItem : public CCMenuItemSpriteExtra {
    public:
      // what rob uses
      cocos2d::ccColor3B m_baseColor = {255, 255, 255};
      cocos2d::ccColor3B m_selectColor = {200, 200, 200};
      static CFMenuItem* create(cocos2d::CCNode* sprite, cocos2d::CCNode* disabledSprite, cocos2d::CCObject* target, cocos2d::SEL_MenuHandler callback);
      static CFMenuItem* create(cocos2d::CCNode* sprite, cocos2d::CCObject* target, cocos2d::SEL_MenuHandler callback);
      void selected() override;
      void unselected() override;
  };
}