#pragma once

#include <vector>
#include <string>

namespace summit::ui {
  class UIManager {
    protected:
      static std::vector<std::string> m_tabs;
    public:
      static std::vector<std::string> getTabs();
      static bool registerTab(std::string);
  };
}