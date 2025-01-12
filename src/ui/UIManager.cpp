#include "UIManager.hpp"

namespace summit::ui {

    std::map<std::string, styles::Style *> styleMap;
    styles::Style *currentStyle = nullptr;

    bool addStyle(styles::Style *style) {
        if (styleMap.contains(style->getId())) return false;
        styleMap[style->getId()] = style;
        return true;
    }

    styles::Style *getStyle(std::string id) {
        if (!styleMap.contains(id)) return nullptr;
        return styleMap.at(id);
    }
    
    styles::Style *getStyle() {
        return currentStyle;
    }

    bool setStyle(std::string id) {
        if (!styleMap.contains(id)) return false;
        currentStyle = styleMap.at(id);
        return true;
    }

    bool setStyle(styles::Style *style) {
        if (!styleMap.contains(style->getId())) return false;
        currentStyle = style;
        return true;
    }
}