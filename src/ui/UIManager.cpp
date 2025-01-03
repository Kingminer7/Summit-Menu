#include "UIManager.hpp"

namespace summit::ui {
    
    std::map<std::string, Style*> styleM = {};
    Style *currentStyle = nullptr;

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