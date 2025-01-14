#pragma once

namespace summit::ui::styles {

inline void getStyles() {}


/**
  @brief What the style is based on.
*/
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
  @brief Called on the type's respective update function. Only called if its the current style.
  @param dt The time since the last update.
  */
  virtual void update(float dt) {};


  /**
  @brief Makes the style's UI show.
  */
  virtual void show() = 0;

  /**
  @brief Makes the style's UI hide.
  */
  virtual void hide() = 0;

  /**
  @brief Makes the style's UI toggle.
  */
  virtual void toggle();
  
  /**
  @brief Tells you if the style's UI is visible.
  @return Whether it's visible or not.
  */
  bool isVisible();

  /**
  @brief Tells you what type the style is.
  @return The style type.
  */
  virtual StyleType getStyleType() = 0;

  /**
  @brief Gets the ID of the style.
  @return The ID of the style.
  */
  virtual std::string getId() = 0;
};
} // namespace summit::ui::style