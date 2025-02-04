#include "CocosUI.hpp"
#include <ui/UIManager.hpp>
#include "nodes/CFMenuItem.hpp"

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
  if (m_popup)
    throw std::runtime_error("Popup already exists");
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

bool CocosUI::UIPopup::setup() {
  CCSize nodeSize = {80, 20};
  auto ws = CCDirector::get()->getWinSize();
  m_buttonMenu->setContentSize(ws);
  m_buttonMenu->setPosition(ws / 2 - (m_mainLayer->getPosition() - m_mainLayer->getContentSize() / 2));
  m_closeBtn->setPosition(m_closeBtn->getScaledContentWidth() / 2, ws.height - m_closeBtn->getScaledContentHeight() / 2);

  tabScroll = ScrollLayer::create({nodeSize.width, 240});
  tabScroll->setContentSize({nodeSize.width, 240});
  tabScroll->ignoreAnchorPointForPosition(false);

  CCMenu *tabScrollMenu = CCMenu::create();
  tabScrollMenu->setContentSize({nodeSize.width, 240});
  auto layout = AxisLayout::create(Axis::Column);
  layout->setAxisReverse(true);
  layout->setAxisAlignment(AxisAlignment::End);
  tabScrollMenu->setLayout(layout);

  float y = 0;
  tabScroll->m_contentLayer->addChildAtPosition(tabScrollMenu, Anchor::Center);
  m_mainLayer->addChildAtPosition(tabScroll, Anchor::Left, {nodeSize.width / 2 + 10, 0});

  for (std::string tab : UIManager::getTabs()) {
    auto bg = CCScale9Sprite::create("square02b_small.png");
    bg->setContentSize(nodeSize * 2);
    bg->setScale(.5f);
    bg->setColor({0,0,0});
    bg->setOpacity(127);
    y += nodeSize.height;

    auto lab = CCLabelBMFont::create(tab.c_str(), "bigFont.fnt");
    lab->limitLabelWidth(nodeSize.width - 5, .5f, .05f);
    
    auto btn = CFMenuItem::create(
        bg, this, menu_selector(CocosUI::UIPopup::onTab)
    );
    btn->setID(tab);
    btn->addChildAtPosition(lab, geode::Anchor::Center);
    btn->m_animationEnabled = false;
    btn->m_colorEnabled = true;
    btn->m_baseColor = {0,0,0};
    btn->m_selectColor = {50,50,50};
    tabScrollMenu->addChild(btn);

    auto hackScroll = ScrollLayer::create({370, 240});
    hackScroll->setContentSize({370, 240});
    hackScroll->ignoreAnchorPointForPosition(false);

    CCMenu *hackScrollMenu = CCMenu::create();
    hackScrollMenu->setContentSize({370, 240});
    auto layout = AxisLayout::create(Axis::Row);
    layout->setAxisAlignment(AxisAlignment::Start);
    layout->setCrossAxisOverflow(true);
    layout->setCrossAxisAlignment(AxisAlignment::End);
    layout->setCrossAxisReverse(true);
    hackScrollMenu->setLayout(layout);

    hackScroll->m_contentLayer->addChildAtPosition(hackScrollMenu, Anchor::Center);
    m_mainLayer->addChildAtPosition(hackScroll, Anchor::Left, {280, 0});
    hackScroll->m_contentLayer->setOpacity(y);

    hackScrolls[tab] = hackScroll;
    if (currentTab != tab) hackScroll->setVisible(false);
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
}
}