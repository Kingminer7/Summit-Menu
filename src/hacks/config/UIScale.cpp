#include "../../ui/UIManager.hpp"
#include "UIScale.hpp"
#include "../../Summit.hpp"

using namespace geode::prelude;

namespace summit::hacks::config {
    void UIScale::init() {
        value = summit::Config::get<float>("config.uiscale", 1.0f);
        auto widget = ui::Widget::create("UIScale")
            ->addComponent(
                ui::FloatInput::create("ui-scale", value,
                    [this](ui::Component *comp, float value) {
                        summit::Config::set("config.uiscale", value);
                })
                ->setType(ui::InputType::Input))
            ->addComponent(ui::Label::create("uiscale-label", "UI Scale"))
            ->setTab("Config")
            ->setExclusivity(ui::Exclusivity::ImGui);;
        ui::registerWidget("UIScale", widget);
    };

    std::string UIScale::getId() {
        return "config.uiscale";
    };

    std::string UIScale::getTab() {
        return "Config";
    };

    void UIScale::update(float) {
        
    };

    RegisterHack(UIScale)
}