#include "ImTabbed.hpp"
#include "../../Summit.hpp"

namespace summit::ui::styles {
    void ImTabbed::init() {
        
    }

    void ImTabbed::update(float) {
        if (!visible) return;
        auto scale = summit::Config::get<float>("config.uiscale", 1.f) * ImGui::GetIO().DisplaySize.x / 1920.f;
        for (auto tab : getTabs()) {
            ImGui::SetNextWindowSize(ImVec2(200 * scale, 275 * scale));
            if (ImGui::Begin(tab.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
                ImGui::SetWindowFontScale(scale / 4.f);
                for (auto widget : getWidgetOrder(tab)) {
                    if (auto comp = getWidget(widget)) {
                        if (comp->getExclusivity() == Exclusivity::All || comp->getExclusivity() == Exclusivity::ImGui || comp->getExclusivity() == Exclusivity::ImTabbed) {
                            comp->renderImgui();
                        }
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