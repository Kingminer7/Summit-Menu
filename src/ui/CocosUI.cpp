#include <Geode/loader/Mod.hpp>

#include "CocosUI.hpp"
#include <ui/UIManager.hpp>
#include "nodes/MenuBall.hpp"
#include "nodes/CFMenuItem.hpp"
#include "ui/widgets/Widget.hpp"

using namespace geode::prelude;

namespace summit::ui::styles {
// main ui
CocosUI *CocosUI::m_instance = nullptr;

void CocosUI::init() {}

void CocosUI::deinit() {
  if (m_popup) {
    m_popup->onClose(nullptr);
  }
}

void CocosUI::open() {
  if (m_open)
    return;
  m_open = true;
  if (m_popup) m_popup->removeMeAndCleanup();
  m_popup = UIPopup::create();
  m_popup->show();
}

void CocosUI::close() {
  if (!m_open)
    return;
  m_open = false;
  if (!m_popup)
    return;
  m_popup->onClose(nullptr);
  m_popup = nullptr;
}

CocosUI *CocosUI::getInstance() {
  if (!m_instance)
    m_instance = new CocosUI;
  return m_instance;
}

StyleBase CocosUI::getStyleBase() { return StyleBase::Cocos; }
std::string CocosUI::getId() { return "CocosUI"; }
void CocosUI::update() {}

// popup
CocosUI::UIPopup *CocosUI::UIPopup::create() {
  auto ret = new UIPopup();
  if (ret->initAnchored(475.f, 270.f, "GJ_square05.png")) {
    ret->autorelease();
    return ret;
  }

  delete ret;
  return nullptr;
}

void addNode(ScrollLayer *layer, std::string id, widgets::Widget *widget) {
  auto node = widget->createCocosNode();
  if (!node) return;
  layer->m_contentLayer->addChild(node);
  node->setID(id);
}

bool CocosUI::UIPopup::setup() {
  setID("cocos-ui"_spr);
  m_mainLayer->setID("main-layer");
  m_bgSprite->setID("popup-bg");
  CCSize nodeSize = {80, 20};
  auto ws = CCDirector::get()->getWinSize();
  m_buttonMenu->setContentSize(ws);
  m_buttonMenu->setPosition(ws / 2 - (m_mainLayer->getPosition() - m_mainLayer->getContentSize() / 2));
  m_buttonMenu->setID("button-menu");
  m_closeBtn->setPosition(m_closeBtn->getScaledContentWidth() / 2, ws.height - m_closeBtn->getScaledContentHeight() / 2);
  m_closeBtn->setID("close-button");

  tabScroll = ScrollLayer::create({nodeSize.width, 240});
  tabScroll->setID("buttons");
  tabScroll->setContentSize({nodeSize.width, 240});
  tabScroll->ignoreAnchorPointForPosition(false);

  CCMenu *tabScrollMenu = CCMenu::create();
  tabScrollMenu->setContentSize({nodeSize.width, 240});
  tabScrollMenu->setID("tab-button-menu");
  auto layout = AxisLayout::create(Axis::Column);
  layout->setAxisReverse(true);
  layout->setAxisAlignment(AxisAlignment::End);
  tabScrollMenu->setLayout(layout);

  float y = 0;
  tabScroll->m_contentLayer->addChildAtPosition(tabScrollMenu, Anchor::Center);
  m_mainLayer->addChildAtPosition(tabScroll, Anchor::Left, {nodeSize.width / 2 + 10, 0});

  for (std::string tab : UIManager::getTabs()) {
    auto btnBg = CCScale9Sprite::create("square02b_001.png");
    btnBg->setID("btn-bg");
    btnBg->setScale(0.25f);
    btnBg->setContentSize(nodeSize * 4);
    btnBg->setColor({0,0,0});
    btnBg->setOpacity(75);
    y += nodeSize.height;

    auto btnLab = CCLabelBMFont::create(tab.c_str(), "bigFont.fnt");
    btnLab->limitLabelWidth(nodeSize.width - 5, .5f, .05f);
    btnLab->setID("btn-label");
    
    auto btn = CFMenuItem::create(
        btnBg, this, menu_selector(CocosUI::UIPopup::onTab)
    );
    btn->setID(tab);
    btn->addChildAtPosition(btnLab, geode::Anchor::Center);
    btn->m_animationEnabled = false;
    btn->m_colorEnabled = true;
    btn->m_baseColor = {0,0,0};
    btn->m_selectColor = {50,50,50};
    tabScrollMenu->addChild(btn);

    auto hackScroll = ScrollLayer::create({370, 240});
    hackScroll->setContentSize({370, 240});
    hackScroll->ignoreAnchorPointForPosition(false);
    hackScroll->setID("tab-" + tab);

    auto scrollBg = CCScale9Sprite::create("square02b_001.png");
    scrollBg->setID("scroll-bg");
    scrollBg->setContentSize({370, 240});
    scrollBg->setColor({0,0,0});
    scrollBg->setOpacity(75);
    hackScroll->addChildAtPosition(scrollBg, Anchor::Center);

    auto layout = AxisLayout::create(Axis::Column);
    layout->setAxisAlignment(AxisAlignment::End);
    layout->setCrossAxisOverflow(true);
    layout->setCrossAxisAlignment(AxisAlignment::End);
    layout->setCrossAxisReverse(true);
    layout->setGrowCrossAxis(true);
    hackScroll->m_contentLayer->setLayout(layout);

    m_mainLayer->addChildAtPosition(hackScroll, Anchor::Left, {280, 0});

    hackScrolls[tab] = hackScroll;
    if (currentTab != tab) hackScroll->setVisible(false);

    bool left = false;

    auto widgets = UIManager::getWidgets(tab);
    for (std::string id : UIManager::getInsertionOrder(tab)) {
      auto widget = widgets[id];
      if (!widget) continue;
      if (!left && (pair.second->getSize() == widgets::WidgetSize::Full || pair.second->getSize() == widgets::WidgetSize::FullDouble)) {
        log::info("double - {}", pair.second->getId());
        
        continue;
      } else if (!cache.empty()) {
        for (auto& pair2 : cache) {
          auto node2 = pair2.second->createCocosNode();
          if (!node2) continue;
          hackScroll->m_contentLayer->addChild(node2);
          node2->setID(pair2.first);
        }
        cache = {};
      }
      left = !left;
      auto node = pair.second->createCocosNode();
      if (!node) continue;
      hackScroll->m_contentLayer->addChild(node);
      node->setID(pair.first);
    }

    for (auto& pair : cache) {
      left = !left;
      auto node = pair.second->createCocosNode();
      log::info("{}", node == nullptr);
      if (!node) continue;
      hackScroll->m_contentLayer->addChild(node);
      node->setID(pair.first);
    }

    hackScroll->m_contentLayer->updateLayout();
  }

  tabScrollMenu->updateLayout();

  if (y > 240) {
    tabScroll->m_contentLayer->setContentHeight(y);
    tabScrollMenu->setContentHeight(y);
  }
  return true;
}

void CocosUI::UIPopup::onTab(CCObject *sender)  {
  if (!sender) return;
  auto node = static_cast<CCNode*>(sender);
  if (auto scroll = hackScrolls[currentTab]) {
    scroll->setVisible(false);
  }
	currentTab = node->getID();
  if (auto scroll = hackScrolls[currentTab]) {
    scroll->setVisible(true);
  }
}

void CocosUI::UIPopup::onClose(CCObject *sender) {
  Popup::onClose(sender);
  CocosUI::getInstance()->close();
  MenuBall::get()->setHandlingTouch(true);
}

void CocosUI::UIPopup::show() {
  Popup::show();
  // 107 k
  // 109 m
  // 55  7
  // + 1 to keep it as km7 :trolley:
  setZOrder(10710955 + 1);
  MenuBall::get()->setHandlingTouch(false);
}
}