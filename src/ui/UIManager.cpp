#include "UIManager.hpp"

namespace summit::ui {
    UIManager *UIManager::instance = nullptr;
    void UIManager::init() {
        widget = Widget::create("root");
        widget->addComponent(Button::create("button2", [](Component *comp) {
            log::info("Button clicked!");
        }));
        widget->addComponent(Toggle::create("toggle", false, [](Component *comp, bool value) {
            log::info("Toggle toggled!");
        }));
        widget->addComponent(Label::create("label", "Hello, world!"));
        widget->addComponent(Button::create("button", [](Component *comp) {
            log::info("Button clicked!");
        }));
    }
    UIManager *UIManager::get()  {
        if (!instance) {
            instance = new UIManager();
            instance->init();
        }
        return instance;
    }
}

$on_mod(Loaded) {
    ImGuiCocos::get().setup([] {
        // this runs after imgui has been setup,
        // its a callback as imgui will be re initialized when toggling fullscreen,
        // so use this to setup any themes and or fonts!
    }).draw([] {
        ImGui::Begin("My awesome window");
        ImGui::GetIO().FontGlobalScale = 2.f;
        summit::ui::UIManager::get()->widget->renderImgui();
        
        ImGui::End();
    });
}