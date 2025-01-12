#include "../UIManager.hpp"
#include "Style.hpp"

namespace summit::ui::styles {
class TestStyle : public Style {
public:
  void init() override {}

  StyleType getStyleType() override { return StyleType::ImGui; }

  std::string getId() override { return "ImTabbed"; }

  void show() override {}

  void hide() override {}
};

RegisterStyle(TestStyle)
} // namespace summit::ui::style