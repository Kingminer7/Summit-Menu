#include "../UIManager.hpp"
#include "Style.hpp"
#include <Config.hpp>
#include <hacks/Hack.hpp>
#include <imgui.h>

namespace summit::ui::styles {
  class TestStyle : public Style {
    public:
      void init() override {}
      void update(float dt) override {
        for (auto tab : hacks::getTabs()) {
          ImGui::SetNextWindowSize(ImVec2(300 * ImGui::GetIO().DisplaySize.x / 2400, 400 * ImGui::GetIO().DisplaySize.x / 2400));
          ImGui::Begin(tab.c_str());
          ImGui::SetWindowFontScale(16 * ImGui::GetIO().DisplaySize.x / 24000);
          ImGui::End();
        }
      }

      StyleType getStyleType() override { return StyleType::ImGui; }
      std::string getId() override { return "ImTabbed"; }

      void show() override {}
      void hide() override {}
  };

  RegisterStyle(TestStyle)
}