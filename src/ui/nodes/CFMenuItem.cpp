#include "CFMenuItem.hpp"

CFMenuItem* CFMenuItem::create(cocos2d::CCNode* sprite, cocos2d::CCNode* disabledSprite, cocos2d::CCObject* target, cocos2d::SEL_MenuHandler callback) {
  auto ret = new CFMenuItem();
  if (ret->init(sprite, disabledSprite, target, callback)) {
    ret->autorelease();
    return ret;
  }

  delete ret;
  return nullptr;
}

CFMenuItem* CFMenuItem::create(cocos2d::CCNode* sprite, cocos2d::CCObject* target, cocos2d::SEL_MenuHandler callback) {
  auto ret = new CFMenuItem();
  if (ret->init(sprite, sprite, target, callback)) {
    ret->autorelease();
    return ret;
  }

  delete ret;
  return nullptr;
}

void CFMenuItem::selected() {
  CCMenuItemSpriteExtra::selected();
  if (!m_colorEnabled || !m_pNormalImage) return;
  if (cocos2d::CCSprite *sprite = geode::cast::typeinfo_cast<cocos2d::CCSprite *>(m_pNormalImage)) {
    sprite->setColor(m_selectColor);
  }
}

void CFMenuItem::unselected() {
  CCMenuItemSpriteExtra::selected();
  if (!m_colorEnabled || !m_pNormalImage) return;
  if (cocos2d::CCSprite *sprite = geode::cast::typeinfo_cast<cocos2d::CCSprite *>(m_pNormalImage)) {
    sprite->setColor(m_baseColor);
  }
}