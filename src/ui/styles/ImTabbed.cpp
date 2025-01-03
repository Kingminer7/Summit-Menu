#include "ImTabbed.hpp"

namespace summit::ui::styles {
    void ImTabbed::init() {
        
    }

    void ImTabbed::update(float) {
        ImGui::Begin("Test");
        ImGui::Text("Hello, world!");
        ImGui::End();
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