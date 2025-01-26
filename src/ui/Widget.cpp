#include "Widget.hpp"
#include <utils/Loader.hpp>
#include <imgui.h>
namespace summit::ui {

  // <tab <id, widget>>
  std::map<std::string, std::map<std::string, Widget *>> tabs = {};

  void Widget::init(std::string id,Component *component) {
    this->id = id;
    this->component = component;
  }

  Widget *Widget::create(std::string id,Component *component) {
    auto w = new Widget;
    w->init(id, component);
    return w;
  }

  Component *Widget::getComponent() {
    return component;
  }

  std::string Widget::getId() {
    return id;
  }

  Widget *Widget::setComponent(Component *component) {
    this->component = component;
    return this;
  }

  bool Widget::registerWidget(std::string tab) {
    if (!tabs.contains(tab)) return false;
    auto* widgets = &tabs.at(tab);
    if (widgets->contains(id)) return false;
    this->tab = tab;
    widgets->insert({id, this});
    return true;
  }

  std::string Widget::getTab() {
    return tab;
  }


  std::string Component::getId() {
    return id;
  }

  std::string Component::getLabel() {
    return label;
  }


  LabelComponent *LabelComponent::setLabel(std::string label) {
    this->label = label;
    return this;
  }

  void LabelComponent::init(std::string id, std::string text) {
    this->id = id;
    this->label = text;
  }

  std::string LabelComponent::getType() {
    return "Label";
  }

  void LabelComponent::imRender() {
    ImGui::Text("%s", label.c_str());
  }
  LabelComponent *LabelComponent::create(std::string id, std::string text) {
    auto lab = new LabelComponent();
    lab->init(id, text);
    return lab;
  }


  ToggleComponent *ToggleComponent::setLabel(std::string label) {
    this->label = label;
    return this;
  }

  void ToggleComponent::init(std::string id, std::string text, bool default_, std::function<void (bool toggled)> callback) {
    this->id = id;
    this->label = text;
    this->toggled = default_;
    this->callback = callback;
  }

  std::string ToggleComponent::getType() {
    return "Toggle";
  }

  void ToggleComponent::imRender() {
    if (ImGui::Checkbox(label.c_str(),&toggled)) {
      callback(toggled);
    }
  }
  
  ToggleComponent *ToggleComponent::create(std::string id, std::string text, bool default_, std::function<void (bool toggled)> callback) {
    auto tog = new ToggleComponent();
    tog->init(id, text, default_, callback);
    return tog;
  }

  ToggleComponent *ToggleComponent::setCallback(std::function<void (bool toggled)> callback) {
    this->callback = callback;
    return this;
  }
  std::function<void (bool toggled)> ToggleComponent::getCallback() {
    return callback;
  }
  bool ToggleComponent::isToggled() {
    return toggled;
  }
  ToggleComponent *ToggleComponent::setToggled(bool toggled, bool triggerCallback) {
    this->toggled = toggled;
    if (triggerCallback) callback(toggled);
    return this;
  }


  std::map<std::string, Widget *> getWidgets(std::string tab) {
    return tabs.at(tab);
  }

  std::map<std::string, std::map<std::string, Widget *>> getWidgets() {
    return tabs;
  }

  Widget *getWidget(std::string id, std::string tab) {
     if (!tabs.contains(tab)) return nullptr;
    auto widgets = tabs.at(tab);
    return widgets.at(tab);
  }
  

  bool registerTab(std::string tab) {
    if (tabs.contains(tab)) return false;
    tabs.insert({tab, {}});
    return true;
  }

  std::vector<std::string> getTabs() {
    std::vector<std::string> keys;
    for (const auto& pair : tabs) {
        keys.push_back(pair.first);
    }
    return keys;
  }
}

$execute {
  summit::ui::registerTab("Global");
}
