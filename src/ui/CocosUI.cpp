#include "CocosUI.hpp"
#include <ui/UIManager.hpp>

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
  if (ret->initAnchored(475.f, 270.f)) {
    ret->autorelease();
    return ret;
  }

  delete ret;
  return nullptr;
}

bool CocosUI::UIPopup::setup() {
  auto ws = CCDirector::get()->getWinSize();
  m_buttonMenu->setContentSize(ws);

  tabScroll = ScrollLayer::create({60, 240});
  tabScroll->setContentSize({60, 240});
  tabScroll->ignoreAnchorPointForPosition(false);
  auto layout = AxisLayout::create(Axis::Column);
  layout->setAxisReverse(true);
  layout->setAxisAlignment(AxisAlignment::End);
  tabScroll->m_contentLayer->setLayout(layout);

  float y = 0;
  m_mainLayer->addChildAtPosition(tabScroll, Anchor::Left, {40, 0});

  for (std::string tab : UIManager::getTabs()) {
    auto bg = CCScale9Sprite::create("square02b_small.png");
    bg->setContentSize({60, 20});
    y += 20;
    
    auto btn = CCMenuItemSpriteExtra::create(
        bg, this, menu_selector(CocosUI::UIPopup::onTab)
    );
    tabScroll->m_contentLayer->addChild(btn);
    tabScroll->m_contentLayer->updateLayout();
  }

  if (y > 240) tabScroll->m_contentLayer->setContentHeight(y);
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