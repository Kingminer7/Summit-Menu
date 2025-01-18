#pragma once

#include "style/Style.hpp"

namespace summit::ui {
    bool addStyle(styles::Style *style);

    styles::Style *getStyle(std::string id);

    styles::Style *getStyle();

    bool setStyle(std::string id);

    #define RegisterStyle(T) $on_mod(Loaded) { addStyle(new T); }
}