#include "Style.hpp"

namespace summit::ui::styles {
void Style::update() {}
void Style::toggle() {
  if (m_open)
    close();
  else
    open();
}
void Style::open() { m_open = true; }
void Style::close() { m_open = false; }
bool Style::isOpen() { return m_open; }
}