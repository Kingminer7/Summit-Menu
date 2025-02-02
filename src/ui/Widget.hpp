#pragma once

namespace summit::ui {
  enum class WidgetType {
    Label,
    Toggle,
    Button,
    Dropdown,
    Float,
    FloatToggle,
    Int,
    IntToggle,
    Color,
    None,
  };

  class Component {
    protected:
      std::string id;
      std::string label;
      std::string tab;
      Component () {}
    public:
      std::string getId();
      std::string getLabel();
      std::string getTab();
      virtual std::string getType() = 0;
      virtual void imRender() = 0;
      bool reg();
  };

  class LabelComponent : public Component {
    protected:
      void init(std::string id, std::string text);
    public:
      LabelComponent *setLabel(std::string label);
      LabelComponent *setTab(std::string tab);
      void imRender() override;
      std::string getType() override;
      static LabelComponent *create(std::string id, std::string text);
  };

  class ToggleComponent : public Component {
    protected:
      void init(std::string id, std::string text, bool default_, std::function<void (bool toggled)> callback);
      bool toggled = false;
      std::function<void (bool toggled)> callback;
    public:
      ToggleComponent *setLabel(std::string label);
      ToggleComponent *setTab(std::string tab);
      void imRender() override;
      std::string getType() override;
      ToggleComponent *setCallback(std::function<void (bool toggled)> callback);
      std::function<void (bool toggled)> getCallback();
      bool isToggled();
      ToggleComponent *setToggled(bool toggled, bool triggerCallback = false);
      static ToggleComponent *create(std::string id, std::string text, bool default_, std::function<void (bool toggled)> callback);
  };

  class ButtonComponent : public Component {
    protected:
      void init(std::string id, std::string text, std::function<void ()> callback);
      std::function<void ()> callback;
    public:
      ButtonComponent *setLabel(std::string label);
      ButtonComponent *setTab(std::string tab);
      void imRender() override;
      std::string getType() override;
      ButtonComponent *setCallback(std::function<void ()> callback);
      std::function<void ()> getCallback();
      static ButtonComponent *create(std::string id, std::string text, std::function<void ()> callback);
  };

  class FloatComponent : public Component {
    protected:
      void init(std::string id, std::string text, float default_, std::function<void (float value)> callback);
      std::function<void (float value)> callback;
      float value;
    public:
      FloatComponent *setTab(std::string tab);
      FloatComponent *setLabel(std::string label);
      void imRender() override;
      std::string getType() override;
      FloatComponent *setCallback(std::function<void (float value)> callback);
      std::function<void (float value)> getCallback();
      FloatComponent *setValue(float value);
      float getValue();
      static FloatComponent *create(std::string id, std::string text, float default_, std::function<void (float value)> callback);
  };
  std::map<std::string, Component *> getComponents(std::string tab);
  std::map<std::string, std::map<std::string, Component *>> getComponents();
  Component *getComponent(std::string id, std::string tab);
  bool registerTab(std::string tab);
  std::vector<std::string> getTabs();
}
