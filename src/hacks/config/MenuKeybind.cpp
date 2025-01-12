#include "../../ui/UIManager.hpp"
#include "../../ui/FontManager.hpp"
#include "../../Summit.hpp"
#include "MenuKeybind.hpp"

using namespace geode::prelude;

namespace summit::hacks::config {

    void MenuKeybind::init() {
        std::vector<std::string> strs;
        auto m = utils::KeyManager::getStringBinds();
        for(std::map<std::string, utils::Key>::iterator it = m.begin(); it != m.end(); ++it) {
            strs.push_back(it->first);
        }
        auto kbW = ui::Widget::create("MenuKeybind")
            ->addComponent(
                ui::Dropdown::create("style", strs, summit::Config::get<std::string>("keybinds.menu", "Tab"),
                    [this, m](ui::Component *comp, std::string value) {
                        utils::KeyManager::getKeybind("open")->key = m.at(value);
                    }))
                    ->addComponent(ui::Label::create("bind-lab", "Menu Keybind (very manual for now)"))
            ->setTab("Config");
        ui::registerWidget("MenuKeybind", kbW);
    };

    std::string MenuKeybind::getId() {
        return "config.fonts";
    };

    std::string MenuKeybind::getTab() {
        return "Config";
    };

    void MenuKeybind::update(float) {
        
    };

    RegisterHack(MenuKeybind)
}