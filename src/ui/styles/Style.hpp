#pragma once

namespace summit::ui::styles {
    enum class BaseType {
        ImGui,
        Cocos
    };

    class Style {
        protected:
            bool visible = false;
        public:
            virtual void init() = 0;
            virtual std::string getId() = 0;
            virtual BaseType getBaseStyle() = 0;
            // Functions as the draw function for imgui styles
            virtual void update(float) = 0;
            virtual void show();
            virtual void hide();
            virtual void toggle();
            bool isVisible();
    };
}