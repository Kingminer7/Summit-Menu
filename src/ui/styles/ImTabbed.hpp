#pragma once

#include "Style.hpp"
#include "../UIManager.hpp"

namespace summit::ui::styles {
    class ImTabbed : public Style {
        protected:
            bool displayed = true;
        public:
            void init() override;
            std::string getId() override { return "ImTabbed"; }
            BaseType getBaseStyle() override { return BaseType::ImGui; }
            void update(float) override;
            void show();
            void hide();
            void toggle();
            bool isVisible();
    };

    RegisterStyle(ImTabbed)
}