#include "../nodes/MenuBall.hpp"
#include "../nodes/CFMenuItem.hpp"
#include <Summit.hpp>
#include "Cocos.hpp"
#include <Geode/Geode.hpp>

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
    float height = 240.f;
    cocos2d::CCSize tabBtnSize = {80, 20};
    cocos2d::CCSize fullHackSize = {370, 30};

    m_tabMenu = cocos2d::CCMenu::create();
    m_tabMenu->setID("tab-menu");
    m_tabMenu->setLayout(geode::AxisLayout::create(geode::Axis::Column)->setCrossAxisOverflow(false)->setAxisAlignment(geode::AxisAlignment::End)->setAxisReverse(true)->setAutoScale(false)->setGap(3.f));
    m_tabMenu->setContentSize({tabBtnSize.width, height});
    m_tabMenu->ignoreAnchorPointForPosition(false);
    m_mainLayer->addChildAtPosition(m_tabMenu, geode::Anchor::Left, {tabBtnSize.width / 2 + 10, 0});

    m_hackScroll = geode::ScrollLayer::create({fullHackSize.width, height});
    m_hackScroll->setID("hack-scroll");
    m_hackScroll->setContentSize({fullHackSize.width, height});
    m_hackScroll->ignoreAnchorPointForPosition(false);
    m_mainLayer->addChildAtPosition(m_hackScroll, geode::Anchor::Right, {-fullHackSize.width / 2 - 10, 0});

    auto btnBg = cocos2d::extension::CCScale9Sprite::create("square02b_001.png");
    btnBg->setID("background");
    btnBg->setContentSize({fullHackSize.width, height});
    btnBg->setColor({0,0,0});
    btnBg->setOpacity(75);
    btnBg->setZOrder(-1);
    m_hackScroll->addChildAtPosition(btnBg, geode::Anchor::Center);

    // I refuse to change this name.
    auto holderBecauseScrollLayerIsSuperStupidAndIHateIt = cocos2d::CCNode::create();
    holderBecauseScrollLayerIsSuperStupidAndIHateIt->setID("dumb-holder");
    m_hackScroll->m_contentLayer->addChildAtPosition(holderBecauseScrollLayerIsSuperStupidAndIHateIt, geode::Anchor::Center);

    auto tabY = -5;

    auto uim = UIManager::get();
    for (auto id : uim->getOrder()) {
      auto tab = uim->getTab(id);
      auto btnBg = cocos2d::extension::CCScale9Sprite::create("square02b_001.png");
      btnBg->setID("btn-bg");
      btnBg->setScale(0.25f);
      btnBg->setContentSize(tabBtnSize * 4);
      btnBg->setColor({0,0,0});
      btnBg->setOpacity(75);
      tabY += tabBtnSize.height + 3.f;
  
      auto btnLab = cocos2d::CCLabelBMFont::create(id.c_str(), "bigFont.fnt");
      btnLab->limitLabelWidth(tabBtnSize.width - 5, .5f, .05f);
      btnLab->setID("btn-label");
      
      auto btn = CFMenuItem::create(
          btnBg, this, menu_selector(CocosUI::onTab)
      );
      btn->setID(id);
      btn->addChildAtPosition(btnLab, geode::Anchor::Center);
      btn->m_animationEnabled = false;
      btn->m_colorEnabled = true;
      btn->m_baseColor = id == m_currentTab ? cocos2d::ccColor3B({160,160,160}) : cocos2d::ccColor3B({0,0,0});
      if (auto img = static_cast<cocos2d::CCSprite *>(btn->getNormalImage())) img->setColor(btn->m_baseColor);
      btn->m_selectColor = {50,50,50};
      m_tabMenu->addChild(btn);

      cocos2d::CCMenu *menu = cocos2d::CCMenu::create();
      menu->setID(id);
      menu->setContentSize({fullHackSize.width, height});
      menu->ignoreAnchorPointForPosition(false);
      menu->setVisible(m_currentTab == id);
      m_hackMenus[id] = menu;
     
      holderBecauseScrollLayerIsSuperStupidAndIHateIt->addChildAtPosition(menu, geode::Anchor::Center);
    }
    m_tabMenu->updateLayout();
    

    return true;
  }

  void CocosUI::onTab(cocos2d::CCObject *sender) {
    if (!sender) return;
    auto node = static_cast<CFMenuItem*>(sender);
    if (!node) return;
    auto old = static_cast<CFMenuItem*>(m_tabMenu->getChildByID(m_currentTab));
    if (old) {
      old->m_baseColor = {0, 0, 0};
      if (auto img = static_cast<cocos2d::CCSprite *>(old->getNormalImage())) img->setColor({0, 0, 0});
    }
    node->m_baseColor = {160, 160, 160};
    if (auto img = static_cast<cocos2d::CCSprite *>(node->getNormalImage())) img->setColor({160, 160, 160});
    if (auto menu = m_hackMenus[m_currentTab]) {
      menu->setVisible(false);
    }
    m_currentTab = node->getID();
    if (auto menu = m_hackMenus[m_currentTab]) {
      menu->setVisible(true);
      m_hackScroll->m_contentLayer->setContentHeight(std::max(m_hackScroll->getContentHeight(), menu->getContentHeight()));
    }
    m_hackScroll->scrollToTop();
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