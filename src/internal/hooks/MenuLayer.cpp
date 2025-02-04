#include <Geode/modify/MenuLayer.hpp>
#include "../../ui/CocosUI.hpp"

using namespace geode::prelude;

class $modify(TML, MenuLayer) {
  bool init() {
    if (!MenuLayer::init()) return false;
    auto p = summit::ui::styles::CocosUI::getInstance();
    p->init();
    auto myButton = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("summitBtn.png"_spr),
			this,
			menu_selector(TML::onSummit)
		);

		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(myButton);

		myButton->setID("summit-menu"_spr);

		menu->updateLayout();
    return true;
  }

  void onSummit(CCObject*) {
    summit::ui::styles::CocosUI::getInstance()->toggle();
	}
};  