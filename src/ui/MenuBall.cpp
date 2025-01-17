#include "MenuBall.hpp"
// #include "../Summit.hpp"
// #include "../ui/UIManager.hpp"
// #include "../KeyManager.hpp"

// TODO: Optimize

using namespace summit::ui;
using namespace geode::prelude;

namespace summit::ui {

MenuBall *MenuBall::m_instance = nullptr;

bool MenuBall::init() {
  if (!CCMenu::init()) {
    return false;
  }

  scheduleUpdate();

  m_instance = this;

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
  auto x = 50.f; // summit::Config::get<float>("ballPosX", 50.f);
  auto y = 50.f; // summit::Config::get<float>("ballPosY", 50.f);
  x = std::clamp(x, -getContentWidth() / 2,
                 CCDirector::get()->getWinSize().width - getContentWidth() / 2);
  y = std::clamp(y, -getContentHeight() / 2,
                 CCDirector::get()->getWinSize().height -
                     getContentHeight() / 2);
  setPosition({x, y});
  // summit::Config::set<float>("ballPosX", x);
  // summit::Config::set<float>("ballPosY", y);

  setID("summit-button"_spr);

  // utils::KeyManager::addKeybind(new utils::Keybind{
  //     "open", "Open Summit Menu", utils::Key::Tab,
  //     [this](bool isRepeat) { if (!isRepeat) onPress(); }});

  return true;
}

MenuBall *MenuBall::get() {
  if (m_instance)
    return m_instance;
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
  if (!isVisible() || !isHandlingTouch())
    return false;
  m_diff = getPosition() - touch->getLocation();
  m_startPos = new CCPoint(touch->getLocation());
  if (getScaledContentSize().width / 2 <
      ccpDistance(m_sprite->getPosition(),
                  convertToNodeSpace(touch->getLocation()))) {
    return false;
  }
  m_moving = false;

  stopAllActions();
  runAction(
      CCEaseSineOut::create(CCScaleTo::create(0.3f, m_scale * m_multiplier)));
  return true;
}

void MenuBall::ccTouchEnded(CCTouch *touch, CCEvent *evt) {
  stopAllActions();
  runAction(CCEaseSineOut::create(CCScaleTo::create(0.3f, m_scale)));
  if (m_moving)
    return;
  m_callback();
}

void MenuBall::ccTouchMoved(CCTouch *touch, CCEvent *evt) {
  if (!m_moving)
    if (ccpDistance(*m_startPos, touch->getLocation()) > 3)
      m_moving = true;
  if (m_moving) {
    auto pos = touch->getLocation() + diff;
    pos.x = std::clamp(pos.x, -getContentWidth() / 2,
                       CCDirector::get()->getWinSize().width -
                           getContentWidth() / 2);
    pos.y = std::clamp(pos.y, -getContentHeight() / 2,
                       CCDirector::get()->getWinSize().height -
                           getContentHeight() / 2);
    setPosition(pos);
    // summit::Config::set<float>("ballPosX", pos.x);
    // summit::Config::set<float>("ballPosY", pos.y);
  }
}

void MenuBall::update(float dt) {
  // setVisible(isRendered());
}

bool MenuBall::isRendered() {
  // if (!summit::Config::get<bool>("config.showball", false)) return false;
  return m_render;
}

void MenuBall::setRendered(bool render) {
  m_render = render;
  setVisible(render);
}

bool MenuBall::isHandlingTouch() {
  // if (!summit::Config::get<bool>("config.showball", false)) return false;
  return m_render && m_handleTouch;
}

void MenuBall::setHandlingTouch(bool handle) { m_handleTouch = handle; }

} // namespace summit::ui

#include <Geode/modify/MenuLayer.hpp>
class $modify(MenuLayer) {
  bool init() {
    if (!MenuLayer::init())
      return false;
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
    if (btn)
      btn->setZOrder(btnZ);
    return highest;
  }
};
