#include "GUI/CCControlExtension/CCScale9Sprite.h"
#include "Geode/Geode.hpp"
#include "../nodes/MenuBall.hpp"
#include "Geode/ui/SceneManager.hpp"
#include "ui/Style.hpp"
#include "Cocos.hpp"

namespace summit::ui::styles {
  void CocosUIStyle::init() {
    
  }

  void CocosUIStyle::deinit() {

  }

  std::string CocosUIStyle::getId() {
    return "CocosUI";
  }

  StyleSystem CocosUIStyle::getSystem() {
    return StyleSystem::Cocos;
  }

  void CocosUIStyle::show() {
    m_visible = true;
    MenuBall::get()->setHandlingTouch(false);
    if (auto ui = CocosUI::create(this)) {
      ui->show();
      // the funny km7 again
      ui->setZOrder(10710955 + 1);
      geode::SceneManager::get()->keepAcrossScenes(ui);
    }
  }

  void CocosUIStyle::hide() {
    m_visible = false;
    MenuBall::get()->setHandlingTouch(true);
    if (auto node = cocos2d::CCScene::get()->getChildByID("km7dev.summit_menu/cocos-ui")) {
      if (auto ui = static_cast<CocosUI *>(node)) {
        ui->onClose(ui);
      }
    }
  }

  void CocosUIStyle::hideFromPopup() {
    m_visible = false;
    
    MenuBall::get()->setHandlingTouch(true);
  }

  // Called for whatever system is used
  // cocos uses CCNode::update, imgui uses... whatever it has, etc
  void CocosUIStyle::update(float dt) {
    
  }

  // Popup

  bool CocosUI::setup(CocosUIStyle *style) {
    this->m_style = style;

    setID("cocos-ui"_spr);
    m_mainLayer->setID("main-layer");
    m_bgSprite->setID("popup-bg");

    auto ws = cocos2d::CCDirector::get()->getWinSize();
    m_buttonMenu->setContentSize(ws);
    m_buttonMenu->setPosition(ws / 2 - (m_mainLayer->getPosition() - m_mainLayer->getContentSize() / 2));
    m_buttonMenu->setID("button-menu");

    m_closeBtn->setPosition(m_closeBtn->getScaledContentWidth() / 2, ws.height - m_closeBtn->getScaledContentHeight() / 2);
    m_closeBtn->setID("close-button");

    // idk some hardcoded constant values ig
    cocos2d::CCSize tabBtnSize = {80, 20};

    m_tabScroll = geode::ScrollLayer::create(tabBtnSize);
    m_tabScroll->setID("tab-btn-scroll");
    m_tabScroll->setContentSize({tabBtnSize.width, 240});
    m_tabScroll->ignoreAnchorPointForPosition(false);
    m_mainLayer->addChildAtPosition(m_tabScroll, geode::Anchor::Left, {tabBtnSize.width / 2 + 10, 0});

    auto btnBg = cocos2d::extension::CCScale9Sprite::create("square02b_001.png");
    btnBg->setID("btn-bg");
    btnBg->setScale(0.25f);
    btnBg->setContentSize({tabBtnSize.width * 4, 240 * 4});
    btnBg->setColor({0,0,0});
    btnBg->setOpacity(75);
    btnBg->setZOrder(-1);
    m_tabScroll->addChildAtPosition(btnBg, geode::Anchor::Center);

    return true;
  }

  void CocosUI::onClose(cocos2d::CCObject *sender) {
    if (sender != this) {
      m_style->hideFromPopup();
    }
    m_closeHandled = true;
    Popup::onClose(sender);
    geode::SceneManager::get()->forget(this);
  }
    
  CocosUI* CocosUI::create(CocosUIStyle *style) {
    if (cocos2d::CCScene::get()->getChildByID("km7dev.summit_menu/cocos-ui")) {
      geode::log::error("There's already a visible CocosUI!");
      return nullptr;
    }
    auto ret = new CocosUI();
    if (ret->initAnchored(475.f, 270.f, style, "GJ_square05.png")) {
      ret->autorelease();
      return ret;
    }

    delete ret;
    return nullptr;
  }

  RegisterStyle(CocosUIStyle)
}