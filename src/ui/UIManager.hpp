#pragma once

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

    #define RegisterStyle(T) $on_mod(Loaded) { summit::ui::addStyle(new T); }
}