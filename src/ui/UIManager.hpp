#pragma once

#include <imgui-cocos.hpp>
#include "Widget.hpp"

using namespace geode::prelude;

namespace summit::ui {
    class UIManager {
        protected:
            UIManager() {}
            static UIManager *instance;
            void init();
        public:
            Widget *widget;
            static UIManager *get();
    };
}