#include "MenuBall.hpp"
#include "../Summit.hpp"
#include "../ui/UIManager.hpp"

using namespace summit::ui;
using namespace geode::prelude;

namespace summit::ui {

MenuBall *MenuBall::instance = nullptr;

bool MenuBall::init() {
  if (!CCMenu::init()) {
    return false;
  }

  scheduleUpdate();

  instance = this;

  m_sprite = CCSprite::createWithSpriteFrameName("summitBtn.png"_spr);
  m_sprite->setScale(.4f);
  m_sprite->setID("sprite");
  addChild(m_sprite);
  setContentSize(m_sprite->getScaledContentSize());
  setContentSize(m_sprite->getScaledContentSize());
  m_sprite->setPosition(getContentSize() / 2);

  CCScene::get()->addChild(this);
  SceneManager::get()->keepAcrossScenes(this);

  setZOrder(9999998);
  auto x = summit::Config::get<float>("ballPosX", 50.f);
  auto y = summit::Config::get<float>("ballPosY", 50.f);
  x = std::clamp(x, -getContentWidth() / 2, CCDirector::get()->getWinSize().width - getContentWidth() / 2);
  y = std::clamp(y, -getContentHeight() / 2, CCDirector::get()->getWinSize().height - getContentHeight() / 2);
  setPosition({x, y});
  summit::Config::set<float>("ballPosX", x);
  summit::Config::set<float>("ballPosY", y);

  setID("summit-button"_spr);

  return true;;
}

MenuBall *MenuBall::get() {
  if (instance)
    return instance;
  auto ret = new MenuBall();
  if (ret && ret->init()) {
    ret->autorelease();
    return ret;
  } else {
    delete ret;
    return nullptr;
  }
}

void MenuBall::registerWithTouchDispatcher() {
  CCTouchDispatcher::get()->addTargetedDelegate(this, -9999999, true);
}

bool MenuBall::ccTouchBegan(CCTouch *touch, CCEvent *evt) {
  // if (CocosMenu::get()) return false;
  if (!isVisible())
    return false;
  diff = getPosition() - touch->getLocation();
  startPos = new CCPoint(touch->getLocation());
  if (getScaledContentSize().width / 2 <
      ccpDistance(m_sprite->getPosition(),
                  convertToNodeSpace(touch->getLocation()))) {
    return false;
  }
  move = false;
  
  stopAllActions();
  runAction(CCEaseSineOut::create(CCScaleTo::create(0.3f, m_scale * m_multiplier)));
  return true;
}

void MenuBall::ccTouchEnded(CCTouch *touch, CCEvent *evt) {
  stopAllActions();
  runAction(CCEaseSineOut::create(CCScaleTo::create(0.3f, m_scale)));
  if (move)
    return;
  onPress();
}

void MenuBall::ccTouchMoved(CCTouch *touch, CCEvent *evt) {
  if (!move)
    if (ccpDistance(*startPos, touch->getLocation()) > 3)
      move = true;
  if (move) {
    auto pos = touch->getLocation() + diff;
    pos.x = std::clamp(pos.x, -getContentWidth() / 2, CCDirector::get()->getWinSize().width - getContentWidth() / 2);
    pos.y = std::clamp(pos.y, -getContentHeight() / 2, CCDirector::get()->getWinSize().height - getContentHeight() / 2);
    setPosition(pos);
    summit::Config::set<float>("ballPosX", pos.x);
    summit::Config::set<float>("ballPosY", pos.y);
  }
}

void MenuBall::onPress() { 
  // CocosMenu::open();
  if (auto uis = summit::ui::getStyle()) uis->toggle();
}

void MenuBall::update(float dt) {
  #ifndef GEODE_IS_ANDROID
  if (summit::Config::get<bool>("config.showball", false)) {
    setVisible(true);
  } else {
    setVisible(false);
  }
  #endif
}

} 

#include <Geode/modify/MenuLayer.hpp>
class $modify(MenuLayer){
  bool init(){
    if (!MenuLayer::init()) return false;
    static bool initialized = false;
    if (!initialized) {
      MenuBall::get();
      initialized = true;
    }
    return true;
  }
};

#include <Geode/modify/CCScene.hpp>

class $modify(CCScene) {
  int getHighestChildZ() {
    int btnZ;
    auto btn = MenuBall::get();
    if (btn) {
      btnZ = btn->getZOrder();
      btn->setZOrder(-1);
    }
    auto highest = CCScene::getHighestChildZ();
    if (btn) btn->setZOrder(btnZ);
    return highest;
  }
};
