#include "ImTabbed.hpp"

namespace summit::ui::styles {
    void ImTabbed::init() {
        
    }

    void ImTabbed::update(float) {
        for (auto tab : getTabs()) {
            if (ImGui::Begin(tab.c_str())) {
                for (auto widget : getWidgets(tab)) {
                    widget.second->renderImgui();
                }
                ImGui::End();
            }
        }
    }

    void ImTabbed::show() {
        Style::show();
    }

    void ImTabbed::hide() {
        Style::hide();
    }

    void ImTabbed::toggle() {
        Style::toggle();
    }
}