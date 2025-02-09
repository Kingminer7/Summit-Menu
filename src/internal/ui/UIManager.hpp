#pragma once

#include "ui/widgets/Widget.hpp"
#include <map>
#include <vector>
#include <string>

namespace summit::ui {
  class UIManager {
    protected:
      static std::vector<std::string> m_tabs;
      static std::map<std::string, std::map<std::string, widgets::Widget *>> m_widgets;
      static std::map<std::string, std::vector<std::string>> m_insertions;
    public:
      static std::vector<std::string> getTabs();
      static bool registerTab(std::string);

      static std::map<std::string, widgets::Widget *> getWidgets(std::string tab);
      static std::map<std::string, widgets::Widget *> getWidgets();
      static std::vector<std::string> getInsertionOrder(std::string tab);
      static bool registerWidget(std::string, widgets::Widget *);
  };
}