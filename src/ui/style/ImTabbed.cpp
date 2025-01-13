#include "../UIManager.hpp"
#include "Style.hpp"
#include <imgui.h>

namespace summit::ui::styles {
class TestStyle : public Style {
public:
  void init() override {}

  StyleType getStyleType() override { return StyleType::ImGui; }

  std::string getId() override { return "ImTabbed"; }

  void update(float dt) override {
    ImGui::Begin("test");
    bool a = true;
    ImGui::Checkbox("Test", &a);
    ImGui::End();
  }

  void show() override {}

  void hide() override {}
};

RegisterStyle(TestStyle)
} // namespace summit::ui::style