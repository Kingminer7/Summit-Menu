#include "../../ui/UIManager.hpp"
#include "Shortcuts.hpp"

using namespace geode::prelude;

namespace summit::hacks::shortcuts {
    void Shortcuts::init() {
        auto widget = ui::Widget::create("Shortcuts")
            ->addComponent(ui::Button::create("Settings", [](ui::Component *comp) {
                OptionsLayer* layer = OptionsLayer::create();
                cocos2d::CCScene* scene = cocos2d::CCDirector::get()->getRunningScene();
                int z = scene->getHighestChildZ();
                if(z == INT_MAX) return;
                layer->setZOrder(z + 1);
                layer->showLayer(false);
                layer->removeFromParentAndCleanup(false);
                scene->addChild(layer);
            }))
            ->setTab("Shortcuts");
        ui::registerWidget("Shortcuts", widget);
    };

    std::string Shortcuts::getId() {
        return "shortcuts.main";
    };

    std::string Shortcuts::getTab() {
        return "Shortcuts";
    };

    void Shortcuts::update(float) {
        
    };

    RegisterHack(Shortcuts)
}