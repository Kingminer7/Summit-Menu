#include "Geode/cocos/layers_scenes_transitions_nodes/CCScene.h"
#include "Geode/loader/Log.hpp"
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
    if (auto ui = CocosUI::create(this)) {
      ui->show();
    }
  }

  void CocosUIStyle::hide() {
    m_visible = false;
    if (auto node = cocos2d::CCScene::get()->getChildByID("km7dev.summit_menu/cocos-ui")) {
      if (auto ui = static_cast<CocosUI *>(node)) {
        ui->onClose(nullptr);
      }
    }
  }

  void CocosUIStyle::hideFromPopup() {
    m_visible = false;
  }

  // Called for whatever system is used
  // cocos uses CCNode::update, imgui uses... whatever it has, etc
  void CocosUIStyle::update(float dt) {
    
  }



  bool CocosUI::setup(CocosUIStyle *style) {
    this->m_style = style;
    return true;
  }

  void CocosUI::onClose(cocos2d::CCObject *sender) {
    Popup::onClose(sender);
    if (sender != nullptr) {
      
    }
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