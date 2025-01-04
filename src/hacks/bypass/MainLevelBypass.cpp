#include "../../ui/UIManager.hpp"
#include "MainLevelBypass.hpp"
#include "../../Summit.hpp"

using namespace geode::prelude;

namespace summit::hacks::bypass {
    void MainLevelBypass::init() {
        toggled = summit::Config::get<bool>("bypass.mainlevels.toggled", false);
        auto widget = ui::Widget::create("bypass.mainlevels")
            ->addComponent(
                ui::Toggle::create("bypass.mainlevels.toggle", toggled,
                    [this](ui::Component *comp, bool value) {
                        this->toggled = value;
                        summit::Config::set("bypass.mainlevels.toggled", value);
                    }))
            ->addComponent(ui::Label::create("bypass.mainlevels.label", "Main Level Bypass"))
            ->setTab("Bypass");
        ui::registerWidget("MainLevelBypass", widget);
    };

    std::string MainLevelBypass::getId() {
        return "bypass.mainlevels";
    };

    std::string MainLevelBypass::getTab() {
        return "Bypass";
    };

    void MainLevelBypass::update(float) {
        
    };

    RegisterHack(MainLevelBypass)
}


#include <Geode/modify/GameLevelManager.hpp>
class $modify(GameLevelManager) {
    GJGameLevel *getMainLevel(int id, bool dGLS) {
        auto level = GameLevelManager::getMainLevel(id, dGLS);
        if (summit::Config::get<bool>("bypass.mainlevels.toggled", false)) {
            level->m_requiredCoins = 0;
        }
        return level;
    }
};