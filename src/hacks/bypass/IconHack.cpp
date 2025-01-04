#include "../../ui/UIManager.hpp"
#include "IconHack.hpp"
#include "../../Summit.hpp"

using namespace geode::prelude;

namespace summit::hacks::bypass {
    void IconHack::init() {
        toggled = summit::Config::get<bool>("bypass.iconhack.toggled", false);
        auto widget = ui::Widget::create("bypass.iconhack")
            ->addComponent(
                ui::Toggle::create("bypass.iconhack.toggle", toggled,
                    [this](ui::Component *comp, bool value) {
                        this->toggled = value;
                        summit::Config::set("bypass.iconhack.toggled", value);
                    }))
            ->addComponent(ui::Label::create("bypass.iconhack.label", "Icon Hack"))
            ->setTab("Bypass");
        ui::registerWidget("IconHack", widget);
    };

    std::string IconHack::getId() {
        return "bypass.iconhack";
    };

    std::string IconHack::getTab() {
        return "Bypass";
    };

    void IconHack::update(float) {
        
    };

    RegisterHack(IconHack)
}


#include <Geode/modify/GameManager.hpp>
class $modify(GameManager) {
    bool isIconUnlocked(int p0, IconType p1) {
        if (summit::Config::get<bool>("bypass.iconhack.toggled", false)) {
            return true;
        }
        return GameManager::isIconUnlocked(p0, p1);
    }

    bool isColorUnlocked(int p0, UnlockType p1) {
        if (summit::Config::get<bool>("bypass.iconhack.toggled", false)) {
            return true;
        }
        return GameManager::isColorUnlocked(p0, p1);
    }
};