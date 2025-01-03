#include "ImTabbed.hpp"

namespace summit::ui::styles {
    void ImTabbed::init() {
        
    }

    void ImTabbed::update(float) {
        for (auto tab : getTabs()) {
            ImGui::SetNextWindowSize(ImVec2(300, 400));
            if (ImGui::Begin(tab.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
                for (auto widget : getWidgetOrder(tab)) {
                    if (auto comp = getWidget(widget)) {
                        comp->renderImgui();
                    }
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