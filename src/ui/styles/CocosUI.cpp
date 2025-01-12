#include "CocosUI.hpp"
#include "../../Summit.hpp"
#include "../MenuBall.hpp"
#include "../UIManager.hpp"

namespace summit::ui::styles {

bool CocosPopup::setup() {
  m_currentTab = summit::Config::get<std::string>("ui.current-tab", "Global");
  m_bgSprite->setID("bg"_spr);
  m_mainLayer->setID("main-layer"_spr);
  m_buttonMenu->setID("button-menu"_spr);
  m_closeBtn->setID("back-btn"_spr);

  tabBtnMenu = CCMenu::create();
  tabBtnMenu->setID("tab-btn-menu"_spr);
  tabBtnMenu->setPosition({10, 10});
  auto layout = AxisLayout::create(Axis::Column);
  layout->setAxisAlignment(AxisAlignment::End);
  layout->setAxisReverse(true);
  tabBtnMenu->setLayout(layout);
  tabBtnMenu->setContentSize({85.f, 280.f});
  tabBtnMenu->ignoreAnchorPointForPosition(true);
  m_mainLayer->addChild(tabBtnMenu);

  CCMenu *tabHolder = CCMenu::create();
  tabHolder->setID("tab-holder"_spr);
  tabHolder->setPosition({105, 10});
  tabHolder->setContentSize({300.f, 280.f});
  m_mainLayer->addChild(tabHolder);

  CCScale9Sprite *bg = CCScale9Sprite::create("square02b_001.png");
  bg->setContentSize({300.f, 280.f});
  bg->setOpacity(100);
  bg->setColor({0, 0, 0});
  bg->setID("tab-bg"_spr);
  bg->setPosition({105, 10});
  bg->ignoreAnchorPointForPosition(true);
  m_mainLayer->addChild(bg);

  auto tabs = summit::ui::getTabs();
  std::reverse(tabs.begin(), tabs.end());
  for (auto &tab : tabs) {
    auto sprite = CCScale9Sprite::create("square02b_001.png");
    sprite->setContentSize({85.f, 20.f});
    sprite->setOpacity(100);
    sprite->setID("bg");
    CCLabelBMFont *label = CCLabelBMFont::create(tab.c_str(), "bigFont.fnt");
    label->limitLabelWidth(80, .575f, 0.01f);
    label->setPosition({42.5f, 10.f});
    label->setID("label");
    auto btn = CCMenuItemSpriteExtra::create(sprite, this,
                                             menu_selector(CocosPopup::onTab));
    btn->addChild(label);
    btn->setID(tab);

    tabBtnMenu->addChild(btn);
    tabBtnMenu->updateLayout();
    m_menuBtns.push_back(btn);

    auto menu = ScrollLayer::create({300.f, 280.f});
    menu->setID(tab);
    m_menus.push_back(menu);
    tabHolder->addChild(menu);

    if (tab == m_currentTab) {
      sprite->setColor({50, 50, 50});
    } else {
      menu->setVisible(false);
      sprite->setColor({0, 0, 0});
    }

    float height = 0.f;
    bool half = false;
    std::vector<Widget *> queue;

    for (auto widget : summit::ui::getWidgets(tab)) {
      if (widget.second->getSize() == CocosSize::Full) {
        if (half) {
          queue.push_back(widget.second);
        } else {
          if (!queue.empty()) {
            for (auto widget : queue) {
              auto node = widget->createCocosNode({300.f, 40.f});
              node->setZOrder(1);
              height += node->getContentSize().height;
              menu->m_contentLayer->setContentSize(
                  {300, clamp<float>(height, 280, FLT_MAX)});
              node->setPosition(
                  {0.f, menu->m_contentLayer->getContentHeight() - height});
              menu->m_contentLayer->addChild(node);
            }
            queue.clear();
          }
          auto node = widget.second->createCocosNode({300.f, 40.f});
          node->setZOrder(1);
          height += node->getContentSize().height;
          menu->m_contentLayer->setContentSize(
              {300, clamp<float>(height, 280, FLT_MAX)});
          node->setPosition(
              {0.f, menu->m_contentLayer->getContentHeight() - height});
          menu->m_contentLayer->addChild(node);
        }
      } else {
        if (!half) {
          if (!queue.empty()) {
            for (auto widget : queue) {
              auto node = widget->createCocosNode({300.f, 40.f});
              node->setZOrder(1);
              height += node->getContentSize().height;
              menu->m_contentLayer->setContentSize(
                  {300, clamp<float>(height, 280, FLT_MAX)});
              node->setPosition(
                  {0.f, menu->m_contentLayer->getContentHeight() - height});
              menu->m_contentLayer->addChild(node);
            }
            queue.clear();
          }
        }
        auto node = widget.second->createCocosNode({150.f, 40.f});
        node->setZOrder(1);
        if (half) {
          node->setPosition(
              {150.f, menu->m_contentLayer->getContentHeight() - height});
        } else {
          height += node->getContentSize().height;
          menu->m_contentLayer->setContentSize(
              {300, clamp<float>(height, 280, FLT_MAX)});
          node->setPosition(
              {0.f, menu->m_contentLayer->getContentHeight() - height});
        }
        menu->m_contentLayer->addChild(node);
        half = !half;
      }
    }
  }

  return true;
}

CocosPopup *CocosPopup::create() {
  auto ret = new CocosPopup();
  if (ret->initAnchored(420.f, 300.f)) {
    ret->autorelease();
    return ret;
  }

  delete ret;
  return nullptr;
}

void CocosPopup::onClose(CCObject *) {
  MenuBall::get()->setHandlingTouch(true);
  Popup::onClose(nullptr);
}

CocosPopup *CocosPopup::get() {
  if (CCScene::get()->getChildByType<CocosPopup>(0)) {
    return CCScene::get()->getChildByType<CocosPopup>(0);
  }
  return nullptr;
}

void CocosPopup::open() {
  auto menu = CocosPopup::get();
  if (!menu) {
    menu = CocosPopup::create();
    menu->show();
  }
}

void CocosPopup::show() {
  auto s = m_mainLayer->getScale();
  m_mainLayer->setScale(0.0f);
  CCScene::get()->addChild(this, 9999999);
  m_mainLayer->runAction(
      CCEaseElasticOut::create(CCScaleTo::create(0.5f, s), 1.2f));
  MenuBall::get()->setHandlingTouch(false);
}

void CocosPopup::onTab(CCObject *sender) {
  auto btn = dynamic_cast<CCMenuItemSpriteExtra *>(sender);
  if (!btn)
    return;
  auto id = btn->getID();
  if (id == m_currentTab)
    return;
  for (auto &menu : m_menus) {
    if (menu->getID() == m_currentTab)
      menu->setVisible(false);
    if (menu->getID() == id)
      menu->setVisible(true);
  }
  for (auto &btn : m_menuBtns) {
    if (btn->getID() == m_currentTab)
      btn->getChildByType<CCScale9Sprite>(0)->setColor({0, 0, 0});
    if (btn->getID() == id)
      btn->getChildByType<CCScale9Sprite>(0)->setColor({50, 50, 50});
  }
  m_currentTab = id;
}

void CocosUI::init() {}

void CocosUI::update(float) {}

void CocosUI::show() {
  Style::show();
  CocosPopup::open();
}

void CocosUI::hide() {
  if (auto menu = CocosPopup::get()) {
    menu->onClose(nullptr);
  }
  Style::hide();
}

void CocosUI::toggle() {
  if (visible && CocosPopup::get())
    hide();
  else
    show();
}
} // namespace summit::ui::styles
