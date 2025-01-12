#include "Style.hpp"

namespace summit::ui::styles {

void Style::toggle() {
  if (visible)
    hide();
  else
    show();
}

bool Style::isVisible() { return visible; }

} // namespace summit::ui::style