#include "../UIManager.hpp"
#include "Style.hpp"
#include <imgui.h>

namespace summit::ui::styles {
  class TestStyle : public Style {
    public:
      void init() override {}
      void update(float dt) override {

      }

      StyleType getStyleType() override { return StyleType::ImGui; }
      std::string getId() override { return "ImTabbed"; }

      void show() override {}
      void hide() override {}
  };

  RegisterStyle(TestStyle)
}