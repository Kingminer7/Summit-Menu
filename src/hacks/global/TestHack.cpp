#include "../../ui/UIManager.hpp"
#include "TestHack.hpp"
#include "../../Summit.hpp"

using namespace geode::prelude;

namespace summit::hacks::global {
    void TestHack::init() {
        value = summit::Config::get<float>("global.testhack.value", 1.0f);
        toggled = summit::Config::get<bool>("global.testhack.toggled", false);
        auto widget = ui::Widget::create("TestHack")
            ->addComponent(
                ui::Toggle::create("test-toggle", toggled,
                    [this](ui::Component *comp, bool value) {
                        this->toggled = value;
                        summit::Config::set("global.testhack.toggled", value);
                    }))
            ->addComponent(ui::Label::create("test-label", "Test Label"))
            ->addComponent(
                ui::FloatInput::create("test-float", value,
                    [this](ui::Component *comp, float value) {
                        this->value = round(value * 1000) / 1000.0f;
                        summit::Config::set("global.testhack.value", .832f);
                })
                ->setMin(0.001f)
                ->setMax(10.000F)
                ->setType(ui::InputType::Slider))
            ->setTab("Global");
        ui::registerWidget("TestHack", widget);
    };

    std::string TestHack::getId() {
        return "global.testhack";
    };

    std::string TestHack::getTab() {
        return "Global";
    };

    void TestHack::update(float) {
        
    };

    RegisterHack(TestHack)
}