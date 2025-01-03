#pragma once

#include "Style.hpp"
#include "../UIManager.hpp"

namespace summit::ui::styles {
    class CocosUI : public Style {
        protected:
            bool displayed = true;
        public:
            void init() override;
            std::string getId() override { return "CocosUI"; }
            BaseType getBaseStyle() override { return BaseType::Cocos; }
            void update(float) override;
            void show();
            void hide();
            void toggle();
            bool isVisible();
    };

    RegisterStyle(CocosUI)
}