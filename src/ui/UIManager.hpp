#pragma once

#include "Widget.hpp"
#include "styles/Style.hpp"
#include <imgui-cocos.hpp>

using namespace geode::prelude;
using namespace summit::ui::styles;

namespace summit::ui {
    Style *getStyle();
    Style *getStyle(std::string style);
    std::string getCurrentStyle();
    void setStyle(std::string style);
    void setStyle(Style *style);
    void init();
    void addStyle(Style *style);

    void registerTab(std::string tab);
    std::vector<std::string> getTabs();
    void removeTab(std::string tab);

    void registerWidget(std::string id, Widget *widget);
    Widget *getWidget(std::string id);
    void removeWidget(std::string id);
    std::map<std::string, Widget*> getWidgets();
    std::map<std::string, Widget*> getWidgets(std::string tab);
    std::vector<std::string> getWidgetOrder();
    std::vector<std::string> getWidgetOrder(std::string tab);

    #define RegisterStyle(T) $on_mod(Loaded) { summit::ui::addStyle(new T); }
    #define RegisterTab(T) $on_mod(Loaded) { summit::ui::registerTab(T); }
    #define RegisterWidget(T) $on_mod(Loaded) { summit::ui::registerWidget(T->getId(), T); }
}