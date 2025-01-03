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

    Widget *Widget::addComponent(Component *component) {
        if (this->components.find(component->getId()) != this->components.end()) {
            log::error("Component with id {} already exists in widget {}.", component->getId(), this->id);
            return this;
        }
        this->components.insert({component->getId(), component});
        this->order.push_back(component->getId());
        return this;
    }

    Widget *Widget::removeComponent(std::string id) {
        if (this->components.find(id) == this->components.end()) {
            log::error("Component with id {} does not exist in widget {}.", id, this->id);
            return this;
        }
        this->components.erase(id);
        return this;
    }

    std::vector<std::string> Widget::getOrder() {
        return this->order;
    }

    Widget *Widget::setTab(std::string tab) {
        this->tab = tab;
        return this;
    }

    std::string Widget::getTab() {
        return this->tab;
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

    Label* Label::setText(std::string text) {
        this->text = text;
        return this;
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

    Button *Button::setCallback(std::function<void(Component *comp)> callback) {
        this->callback = callback;
        return this;
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

    Toggle *Toggle::setValue(bool value) {
        this->value = value;
        return this;
    }

    bool Toggle::getValue() {
        return this->value;
    }

    // Int Input

    void IntInput::init(std::string id, int value, std::function<void(Component *comp, int value)> callback) {
        this->id = id;
        this->value = value;
        this->callback = callback;
    }

    IntInput *IntInput::create(std::string id, int value, std::function<void(Component *comp, int value)> callback) {
        IntInput *intInput = new IntInput;
        intInput->init(id, value, callback);
        return intInput;
    }

    void IntInput::renderImgui() {
        if (type == InputType::Slider) {
            if (ImGui::SliderInt(fmt::format("##{}", this->id).c_str(), &this->value, min, max)) {
                this->callback(this, this->value);
            }
        } else if (type == InputType::Input) {
            if (ImGui::InputInt(fmt::format("##{}", this->id).c_str(), &this->value)) {
                this->callback(this, this->value);
            }
        } else if (type == InputType::Drag) {
            if (ImGui::DragInt(fmt::format("##{}", this->id).c_str(), &this->value, 1, min, max)) {
                this->callback(this, this->value);
            }
        }
    }

    CCNode *IntInput::createCocosNode() {
        return nullptr;
    }

    IntInput *IntInput::setValue(int value) {
        this->value = value;
        return this;
    }

    int IntInput::getValue() {
        return this->value;
    }

    IntInput *IntInput::setType(InputType type) {
        this->type = type;
        return this;
    }

    InputType IntInput::getType() {
        return this->type;
    }

    IntInput *IntInput::setMin(int min) {
        this->min = min;
        return this;
    }

    int IntInput::getMin() {
        return this->min;
    }

    IntInput *IntInput::setMax(int max) {
        this->max = max;
        return this;
    }

    int IntInput::getMax() {
        return this->max;
    }

    // Float Input

    void FloatInput::init(std::string id, float value, std::function<void(Component *comp, float value)> callback) {
        this->id = id;
        this->value = value;
        this->callback = callback;
    }

    FloatInput *FloatInput::create(std::string id, float value, std::function<void(Component *comp, float value)> callback) {
        FloatInput *floatInput = new FloatInput;
        floatInput->init(id, value, callback);
        return floatInput;
    }

    void FloatInput::renderImgui() {
        if (type == InputType::Slider) {
            if (ImGui::SliderFloat(fmt::format("##{}", this->id).c_str(), &this->value, min, max)) {
                this->callback(this, this->value);
            }
        } else if (type == InputType::Input) {
            if (ImGui::InputFloat(fmt::format("##{}", this->id).c_str(), &this->value)) {
                this->callback(this, this->value);
            }
        } else if (type == InputType::Drag) {
            if (ImGui::DragFloat(fmt::format("##{}", this->id).c_str(), &this->value, 1.f, min, max)) {
                this->callback(this, this->value);
            }
        }
    }

    CCNode *FloatInput::createCocosNode() {
        return nullptr;
    }

    FloatInput *FloatInput::setValue(float value) {
        this->value = value;
        return this;
    }

    float FloatInput::getValue() {
        return this->value;
    }

    FloatInput *FloatInput::setType(InputType type) {
        this->type = type;
        return this;
    }

    InputType FloatInput::getType() {
        return this->type;
    }

    FloatInput *FloatInput::setMin(float min) {
        this->min = min;
        return this;
    }

    float FloatInput::getMin() {
        return this->min;
    }

    FloatInput *FloatInput::setMax(float max) {
        this->max = max;
        return this;
    }

    float FloatInput::getMax() {
        return this->max;
    }

    // Line Break

    void LineBreak::init(std::string id) {
        this->id = id;
    }

    LineBreak *LineBreak::create(std::string id) {
        LineBreak *lineBreak = new LineBreak;
        lineBreak->init(id);
        return lineBreak;
    }

    void LineBreak::renderImgui() {
        ImGui::NewLine();
        ImGui::NewLine();
    }

    CCNode *LineBreak::createCocosNode() {
        return nullptr;
    }
}