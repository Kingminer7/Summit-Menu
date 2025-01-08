#include "../../ui/UIManager.hpp"
#include "ShowBall.hpp"
#include "../../Summit.hpp"

using namespace geode::prelude;

namespace summit::hacks::config {
    void ShowBall::init() {
        toggled = summit::Config::get<bool>("config.showball", false);
        auto widget = ui::Widget::create("config.showball")
            ->addComponent(
                ui::Toggle::create("config.showball.toggle", toggled,
                    [this](ui::Component *comp, bool value) {
                        this->toggled = value;
                        summit::Config::set("config.showball", value);
                    }))
            ->addComponent(ui::Label::create("config.showball.label", "Show Menu Ball"))
            ->setTab("Config");
        ui::registerWidget("ShowBall", widget);
    };

    std::string ShowBall::getId() {
        return "config.showball";
    };

    std::string ShowBall::getTab() {
        return "Config";
    };

    void ShowBall::update(float) {
        
    };

    RegisterHack(ShowBall)
}