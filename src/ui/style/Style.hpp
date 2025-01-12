#pragma once

namespace summit::ui::styles {

inline void getStyles() {}

enum class StyleType {
  ImGui,
  Cocos,
};

class Style {
protected:
  bool visible = false;

public:
  /**
  @brief Calls when the style is initialized.
  */
  virtual void init() = 0;
  /**
  @brief Cocos: CCScheduler update forward. ImGui: ImGui draw forward.
  */
  virtual void update(float dt) {};

  virtual void show() = 0;
  virtual void hide() = 0;
  virtual void toggle();
  bool isVisible();

  virtual StyleType getStyleType() = 0;
  virtual std::string getId() = 0;
};
} // namespace summit::ui::style