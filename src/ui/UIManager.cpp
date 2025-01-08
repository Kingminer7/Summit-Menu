#include "UIManager.hpp"
#include "FontManager.hpp"

namespace summit::ui {
    
    std::vector<std::string> tabs = {};

    std::map<std::string, Style*> styleM = {};
    Style *currentStyle = nullptr;

    std::map<std::string, Widget*> widgets = {};
    std::vector<std::string> widgetOrder = {};

    Style *getStyle() {
        return currentStyle;
    }

    Style *getStyle(std::string style) {
        return styleM[style];
    }

    std::string getCurrentStyle() {
        if (!currentStyle) return "";
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
    }

    void init() {
        initFonts();
        // #ifdef GEODE_IS_MOBILE
        setStyle("CocosUI");
        // #else
        // setStyle("ImTabbed");
        // #endif
    }

    void registerWidget(std::string id, Widget *widget) {
        widgets[id] = widget;
        widgetOrder.push_back(id);
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

    std::vector<std::string> getWidgetOrder() {
        //reverse it
        std::vector<std::string> reversed = widgetOrder;
        std::reverse(reversed.begin(), reversed.end());
        return reversed;
    }

    std::vector<std::string> getWidgetOrder(std::string tab) {
        std::vector<std::string> tabOrder = {};
        for (auto id : widgetOrder) {
            if (widgets[id]->getTab() == tab) {
                tabOrder.push_back(id);
            }
        }
        std::reverse(tabOrder.begin(), tabOrder.end());
        return tabOrder;
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

    RegisterTab("Global")
    RegisterTab("Player")
    RegisterTab("Bypass")
    RegisterTab("Config")
    RegisterTab("Shortcuts")
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
