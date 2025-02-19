#pragma once

#include <string>
namespace summit::ui {
  enum class StyleSystem {
    ImGui,
    Cocos,
  };
  class Style {
    public:
      virtual void init() = 0;
      virtual void deinit() = 0;

      virtual std::string getId() = 0;
      virtual StyleSystem getSystem() = 0;

      // Called for whatever system is used
      // cocos uses CCNode::update, imgui uses... whatever it has, etc
      virtual void update(float dt) {}
  };
}