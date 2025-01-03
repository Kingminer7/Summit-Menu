#include "Style.hpp"

namespace summit::ui::styles {
    void Style::show() {
        this->visible = true;
    }

    void Style::hide() {
        this->visible = false;
    }

    void Style::toggle() {
        this->visible = !this->visible;
    }

    bool Style::isVisible() {
        return this->visible;
    }
}