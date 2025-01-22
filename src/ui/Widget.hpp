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
      virtual void init() = 0;
    public:
      std::string getId();
      std::string getLabel();
      virtual std::string getType() = 0;
      virtual void imRender() = 0;
  };

  class Widget {
    protected:
      std::string id;
      std::string tab;
      Component *component;
      std::map<std::string, Component*> subs;

      void init(std::string id, Component *component);
      Widget () {}
    public:
      static Widget *create(std::string id, Component *component);
      Component *getComponent();
      std::string getId();
      std::string getTab();
      bool registerWidget(std::string tab);
      Widget *setComponent(Component *component);
  };

  class LabelComponent : public Component {
    protected:
      void init() override;
    public:
      LabelComponent *setLabel(std::string label);
      void imRender() override;
  };

  class ToggleComponent : public Component {
    protected:
      void init() override;
      bool toggled = false;
      std::function<void (bool toggled)> callback;
    public:
      ToggleComponent *setLabel(std::string label);
      ToggleComponent *setCallback(std::function<void (bool toggled)> callback);
      std::function<void (bool toggled)> getCallback();
      bool isToggled();
      ToggleComponent *setToggled(bool toggled, bool triggerCallback = false);
      void imRender() override;
  };

  class ButtonComponent : public Component {
    protected:
      void init() override;
      std::function<void ()> callback;
    public:
      ButtonComponent *setLabel(std::string label);
      ButtonComponent *setCallback(std::function<void ()> callback);
      std::function<void ()> getCallback();
      void imRender() override;
  };

  class FloatComponent : public Component {
    protected:
      void init() override;
      std::function<void ()> callback;
      float value = 0.f;
    public:
      FloatComponent *setLabel(std::string label);
      FloatComponent *setCallback(std::function<void ()> callback);
      std::function<void ()> getCallback();
      void imRender() override;
  };

  std::map<std::string, Widget *> getWidgets(std::string tab);
  Widget *getWidget(std::string id, std::string tab);
  bool registerTab(std::string tab);
}