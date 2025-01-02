#include "Widget.hpp"
#include <imgui.h>

namespace summit::ui {
    // Widget
    Widget *Widget::create(std::string id) {
        Widget *widget = new Widget();
        widget->init(id);
        return widget;
    }

    void Widget::init(std::string id) {
        this->id = id;
    }

    std::string Widget::getId() {
        return this->id;
    }

    Component *Widget::getComponent(std::string id) {
        return this->components[id];
    }

    std::unordered_map<std::string, Component*> Widget::getComponents() {
        return this->components;
    }

    void Widget::addComponent(Component *component) {
        if (this->components.find(component->getId()) != this->components.end()) {
            log::error("Component with id {} already exists in widget {}.", component->getId(), this->id);
            return;
        }
        this->components.insert({component->getId(), component});
        this->order.push_back(component->getId());
    }

    void Widget::removeComponent(std::string id) {
        if (this->components.find(id) == this->components.end()) {
            log::error("Component with id {} does not exist in widget {}.", id, this->id);
            return;
        }
        this->components.erase(id);
    }

    void Widget::renderImgui() {
        ImGui::NewLine();
        for (std::string id : this->order) {
            ImGui::SameLine();
            if (auto comp = this->components[id]) {
                comp->renderImgui();
            }
        }
    }

    CCNode *Widget::createCocosNode() {
        // Create widget node
        return nullptr;
    }

    // Component

    std::string Component::getId() {
        return this->id;
    }

    // Label

    void Label::init(std::string id, std::string text) {
        this->id = id;
        this->text = text;
    }

    Label *Label::create(std::string id, std::string text) {
        Label *label = new Label;
        label->init(id, text);
        return label;
    }

    void Label::setText(std::string text) {
        this->text = text;
    }

    std::string Label::getText() {
        return this->text;
    }

    void Label::renderImgui() {
        ImGui::Text("%s", this->text.c_str());
    }

    CCNode *Label::createCocosNode() {
        // Create label node
        return nullptr;
    }

    // Button

    void Button::init(std::string id, std::function<void(Component *comp)> callback) {
        this->id = id;
        this->callback = callback;
    }

    Button *Button::create(std::string id, std::function<void(Component *comp)> callback) {
        Button *button = new Button;
        button->init(id, callback);
        return button;
    }

    void Button::renderImgui() {
        if (ImGui::Button(this->id.c_str())) {
            this->callback(this);
        }
    }

    CCNode *Button::createCocosNode() {
        return nullptr;
    }

    void Button::setCallback(std::function<void(Component *comp)> callback) {
        this->callback = callback;
    }

    std::function<void(Component *comp)> Button::getCallback() {
        return this->callback;
    }

    // Toggle

    void Toggle::init(std::string id, bool value, std::function<void(Component *comp, bool value)> callback) {
        this->id = id;
        this->value = value;
        this->callback = callback;
    }

    Toggle *Toggle::create(std::string id, bool value, std::function<void(Component *comp, bool value)> callback) {
        Toggle *toggle = new Toggle;
        toggle->init(id, value, callback);
        return toggle;
    }

    void Toggle::renderImgui() {
        if (ImGui::Checkbox(fmt::format("##{}", this->id).c_str(), &this->value)) {
            this->callback(this, this->value);
        }
    }

    CCNode *Toggle::createCocosNode() {
        return nullptr;
    }

    void Toggle::setValue(bool value) {
        this->value = value;
    }

    bool Toggle::getValue() {
        return this->value;
    }
}