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
  class Widget {
    protected:
      void init();
    public:
      static Widget *create(WidgetType type);
  };

  std::map<std::string, Widget *> getWidgets(std::string tab);
  Widget *getWidget(std::string id, std::string tab);
}