#include "MenuBall.hpp"
#include <Loader.hpp>
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
    m_sprite->setPosition(getContentSize() / 2);

    CCScene::get()->addChild(this);
    SceneManager::get()->keepAcrossScenes(this);

    setZOrder(9999998);
    auto x = 50.f; // summit::Config::get<float>("config.ball-x", 50.f);
    auto y = 50.f; // summit::Config::get<float>("config.ball-y", 50.f);
    // m_scale = summit::Config::set<float>("config.ball-scale", y);
    m_scale = std::clamp(m_scale, 0.25f, 3.f);
    x = std::clamp(x, -getContentWidth() / 2,
                  CCDirector::get()->getWinSize().width - getContentWidth() / 2);
    y = std::clamp(y, -getContentHeight() / 2,
                  CCDirector::get()->getWinSize().height -
                      getContentHeight() / 2);
    setPosition({x, y});
    // summit::Config::set<float>("config.ball-x", x);
    // summit::Config::set<float>("config.ball-y", y);
    // summit::Config::set<float>("config.ball-scale", m_scale);

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
    if (!m_callback) {
      log::error("Missing callback for menu ball!");
      return;
    }
    m_callback();
  }

  void MenuBall::ccTouchMoved(CCTouch *touch, CCEvent *evt) {
    if (!m_moving)
      if (ccpDistance(*m_startPos, touch->getLocation()) > 3)
        m_moving = true;
    if (m_moving) {
      auto pos = touch->getLocation() + m_diff;
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


  std::function<void()> MenuBall::getCallback() {
    return m_callback;
  }
  void MenuBall::setCallback(std::function<void()> callback) {
    m_callback = callback;
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

}

$execute {
  summit::Loader::onLoad([](){
  MenuBall::get();
  }, 0, summit::LoadTime::MenuLayer);
}

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
