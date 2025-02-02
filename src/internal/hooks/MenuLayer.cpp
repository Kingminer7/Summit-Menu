#include "Geode/loader/Loader.hpp"
#include <Geode/modify/MenuLayer.hpp>
#include "../../ui/CocosUI.hpp"

using namespace geode::prelude;

class $modify(TML, MenuLayer) {
  bool init() {
    if (!MenuLayer::init()) return false;
    queueInMainThread([this] () {
      auto p = summit::ui::styles::CocosUI::getInstance();
      p->init();
      p->open();
    });
    return true;
  }
};  