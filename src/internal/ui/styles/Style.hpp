#pragma once

namespace summit::ui::styles {
  enum class StyleBase {
    Cocos,
    ImGui,
  };

  class Style {
    protected:
      bool m_open = false;
    public:
      virtual void init() = 0;
      virtual void deinit() = 0;
      virtual StyleBase getStyleBase() = 0;
      virtual std::string getId() = 0;
      virtual void update();
      virtual void open();
      virtual void close();
      void toggle();
      bool isOpen();
  };
}