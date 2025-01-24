#include "Widget.hpp"
#include <imgui.h>
namespace summit::ui {

  // <tab <id, widget>>
  std::map<std::string, std::map<std::string, Widget *>> tabs = {};

  void Widget::init(std::string id,Component *component) {
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
    auto widgets = tabs.at(tab);
    if (widgets.contains(id)) return false;
    this->tab = tab;
    widgets.insert({id, this});
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

  void LabelComponent::init() {

  }

  void LabelComponent::imRender() {
    ImGui::Text("%s", label.c_str());
  }


  std::map<std::string, Widget *> getWidgets(std::string tab) {
    return tabs.at(tab);
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
    std::vector<int> keys;
    for (const auto& pair : tabs) {
        keys.push_back(pair.first);
    }
    return keys;
  }
}

$on_mod(Loaded) {
  summit::ui::registerTab("Global");
}
