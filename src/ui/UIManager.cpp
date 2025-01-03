#include "UIManager.hpp"

namespace summit::ui {
    
    std::vector<std::string> tabs = {};

    std::map<std::string, Style*> styleM = {};
    Style *currentStyle = nullptr;
    std::map<std::string, Widget*> widgets = {};

    Style *getStyle() {
        return currentStyle;
    }

    Style *getStyle(std::string style) {
        return styleM[style];
    }

    std::string getCurrentStyle() {
        return currentStyle->getId();
    }

    void setStyle(std::string style) {
        currentStyle = styleM[style];
    }

    void setStyle(Style *style) {
        currentStyle = style;
    }

    void addStyle(Style *style) {
        style->init();
        styleM[style->getId()] = style;
        log::info("Added style: {}", style->getId());
    }

    void init() {
        #ifdef GEODE_IS_MOBILE
        setStyle("CocosUI");
        #else
        setStyle("ImTabbed");
        #endif
    }

    void registerWidget(std::string id, Widget *widget) {
        widgets[id] = widget;
    }

    Widget *getWidget(std::string id) {
        return widgets[id];
    }

    void removeWidget(std::string id) {
        widgets.erase(id);
    }

    std::map<std::string, Widget*> getWidgets() {
        return widgets;
    }

    std::map<std::string, Widget*> getWidgets(std::string tab) {
        std::map<std::string, Widget*> tabWidgets = {};
        for (auto widget : widgets) {
            if (widget.second->getTab() == tab) {
                tabWidgets[widget.first] = widget.second;
            }
        }
        return tabWidgets;
    }

    void registerTab(std::string tab) {
        if (std::find(tabs.begin(), tabs.end(), tab) == tabs.end()) {
            tabs.push_back(tab);
        } else {
            log::warn("Tab {} already exists.", tab);
        }
    }

    void removeTab(std::string tab) {
        tabs.erase(std::remove(tabs.begin(), tabs.end(), tab), tabs.end());
    }

    std::vector<std::string> getTabs() {
        return tabs;
    }

    RegisterTab("Test Tab")
    RegisterTab("Test Tab 2")
    RegisterWidget(Widget::create("test")->setTab("Test Tab")->addComponent(Label::create("test", "Hello, World!")));
    RegisterWidget(Widget::create("speedheck")->setTab("Test Tab")->addComponent(Toggle::create("speedheck", false, [](Component *comp, bool value) {
        log::info("Speedheck: {}", value);
    }))->addComponent(Label::create("test", "Totally speedhack!"))->addComponent(FloatInput::create("speed", 0.0f, [](Component *comp, float value) {
        log::info("Speed: {}", value);
    })->setMin(0.0f)->setMax(10.0f)->setType(InputType::Slider)));
}

using namespace summit::ui;

$on_mod(Loaded) {
    ImGuiCocos::get().setup([] {
        init();
    }).draw([] {
        auto style = getStyle();
        if (style && style->getBaseStyle() == styles::BaseType::ImGui) {
            style->update(ImGui::GetIO().DeltaTime);
        }
    });
}