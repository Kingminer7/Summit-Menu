#include "Widget.hpp"
#include <utils/Loader.hpp>
#include <imgui.h>
namespace summit::ui {
  // <tab <id, widget>>
  std::map<std::string, std::map<std::string, Component *>> tabs = {};


  std::string Component::getId() {
    return id;
  }

  std::string Component::getLabel() {
    return label;
  }

  std::string Component::getTab() {
    return tab;
  }

  bool Component::reg() {
    if (!tabs.contains(tab)) return false;
    auto* widgets = &tabs.at(tab);
    if (widgets->contains(id)) return false;
    widgets->insert({id, this});
    return true;
  }


  LabelComponent *LabelComponent::setLabel(std::string label) {
    this->label = label;
    return this;
  }

  LabelComponent *LabelComponent::setTab(std::string tab) {
    this->tab = tab;
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

  ToggleComponent *ToggleComponent::setTab(std::string tab) {
    this->tab = tab;
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


  ButtonComponent *ButtonComponent::setLabel(std::string label) {
    this->label = label;
    return this;
  }

  ButtonComponent *ButtonComponent::setTab(std::string tab) {
    this->tab = tab;
    return this;
  }

  void ButtonComponent::init(std::string id, std::string text, std::function<void ()> callback) {
    this->id = id;
    this->label = text;
    this->callback = callback;
  }

  std::string ButtonComponent::getType() {
    return "Button";
  }

  void ButtonComponent::imRender() {
    if (ImGui::Button(label.c_str())) {
      callback();
    }
  }
  
  ButtonComponent *ButtonComponent::create(std::string id, std::string text, std::function<void ()> callback) {
    auto tog = new ButtonComponent();
    tog->init(id, text, callback);
    return tog;
  }

  ButtonComponent *ButtonComponent::setCallback(std::function<void ()> callback) {
    this->callback = callback;
    return this;
  }

  std::function<void ()> ButtonComponent::getCallback() {
    return callback;
  }


  FloatComponent *FloatComponent::setLabel(std::string label) {
    this->label = label;
    return this;
  }

  FloatComponent *FloatComponent::setTab(std::string tab) {
    this->tab = tab;
    return this;
  }

  void FloatComponent::init(std::string id, std::string text, float default_, std::function<void (float value)> callback) {
    this->id = id;
    this->label = text;
    this->value = default_;
    this->callback = callback;
  }

  std::string FloatComponent::getType() {
    return "Float";
  }

  CCTextInputNode *node;

  void FloatComponent::imRender() {
    if (!node) node = CCTextInputNode::create(0, 0, "a", "chatFont.fnt");
    if (ImGui::InputFloat(label.c_str(), &value)) {
      callback(value);
    }
  }
  
  FloatComponent *FloatComponent::create(std::string id, std::string text, float default_, std::function<void (float value)> callback) {
    auto tog = new FloatComponent();
    tog->init(id, text, default_, callback);
    return tog;
  }

  FloatComponent *FloatComponent::setCallback(std::function<void (float value)> callback) {
    this->callback = callback;
    return this;
  }

  std::function<void (float value)> FloatComponent::getCallback() {
    return callback;
  }

  float FloatComponent::getValue() {
    return value;
  }

  FloatComponent *FloatComponent::setValue(float value) {
    this->value = value;
    return this;
  }


  std::map<std::string, Component *> getComponents(std::string tab) {
    return tabs.at(tab);
  }

  std::map<std::string, std::map<std::string, Component *>> getComponents() {
    return tabs;
  }

  Component *getComponent(std::string id, std::string tab) {
     if (!tabs.contains(tab)) return nullptr;
    auto components = tabs.at(tab);
    return components.at(tab);
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
  summit::ui::registerTab("Level");
  summit::ui::registerTab("Shortcuts");
}
