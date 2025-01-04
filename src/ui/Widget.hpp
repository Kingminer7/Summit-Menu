#pragma once

#include <imgui.h>
using namespace geode::prelude;

namespace summit::ui {
    enum class Exclusivity {
        // Categories
        All,
        ImGui,
        Cocos,
        // Specifics
        ImTabbed,
        CocosUI
    };

    class Component {
        protected:
            std::string id;
            Component() {};
        public:
            std::string getId();
            virtual void renderImgui() = 0;
            virtual CCNode *createCocosNode() = 0;
    };

    class Widget {
        protected:
            std::vector<std::string> order;
            std::unordered_map<std::string, Component*> components;
            std::string id;
            std::string tab;
            Exclusivity exclusivity = Exclusivity::All;

            Widget() {};

            void init(std::string id);
        public:
            static Widget *create(std::string id);

            std::string getId();
            Component *getComponent(std::string id);
            template <typename T>
            T *getComponentWithType(std::string id) {
                if (this->components[id])
                    return dynamic_cast<T*>(this->components[id]);
                return nullptr;
            }
            std::unordered_map<std::string, Component*> getComponents();
            std::vector<std::string> getOrder();
            Widget *addComponent(Component *component);
            Widget *removeComponent(std::string id);
            Widget *setTab(std::string tab);
            std::string getTab();
            Widget *setExclusivity(Exclusivity exclusivity);
            Exclusivity getExclusivity();
            void renderImgui();
            CCNode *createCocosNode();
    };

    class Label : public Component {
        protected:
            std::string text;
            void init(std::string id, std::string text);
            std::pair<std::string, std::string>font;
        public:
            static Label *create(std::string id, std::string text);
            Label *setText(std::string text);
            std::string getText();
            Label *setFont(std::pair<std::string, std::string>font);
            std::pair<std::string, std::string>getFont();
            void renderImgui() override;
            CCNode *createCocosNode() override;
    };

    class Button : public Component {
        protected:
            std::function<void(Component *comp)> callback;
            void init(std::string id, std::function<void(Component *comp)> callback);
            std::pair<std::string, std::string>font;
        public:
            static Button *create(std::string id, std::function<void(Component *comp)> callback);
            Button *setCallback(std::function<void(Component *comp)> callback);
            std::function<void(Component *comp)> getCallback();
            Button *setFont(std::pair<std::string, std::string>font);
            std::pair<std::string, std::string>getFont();
            void renderImgui() override;
            CCNode *createCocosNode() override;
    };

    class Toggle : public Component {
        protected:
            bool value;
            std::function<void(Component *comp, bool value)> callback;
            void init(std::string id, bool value, std::function<void(Component *comp, bool value)> callback);
        public:
            static Toggle *create(std::string id, bool value, std::function<void(Component *comp, bool value)> callback);
            Toggle *setValue(bool value);
            bool getValue();
            Toggle *setCallback(std::function<void(Component *comp, bool value)> callback);
            std::function<void(Component *comp, bool value)> getCallback();
            void renderImgui() override;
            CCNode *createCocosNode() override;
    };

    class LineBreak : public Component {
        protected:
            void init(std::string id);
        public:
            static LineBreak *create(std::string id);
            void renderImgui() override;
            CCNode *createCocosNode() override;
    };

    enum class InputType {
        Slider,
        Input,
        Drag
    };

    class IntInput : public Component {
        protected:
            int value;
            int min = 0;
            int max = 0;
            InputType type = InputType::Slider;
            std::function<void(Component *comp, int value)> callback;
            std::pair<std::string, std::string>font;
            void init(std::string id, int value, std::function<void(Component *comp, int value)> callback);
        public:
            static IntInput *create(std::string id, int value, std::function<void(Component *comp, int value)> callback);
            IntInput *setValue(int value);
            int getValue();
            IntInput *setCallback(std::function<void(Component *comp, int value)> callback);
            std::function<void(Component *comp, int value)> getCallback();
            IntInput *setType(InputType type);
            InputType getType();
            IntInput *setMin(int min);
            int getMin();
            IntInput *setMax(int max);
            int getMax();
            IntInput *setFont(std::pair<std::string, std::string>font);
            std::pair<std::string, std::string>getFont();
            void renderImgui() override;
            CCNode *createCocosNode() override;
    };

    class FloatInput : public Component {
        protected:
            float value;
            float min = 0;
            float max = 5;
            InputType type = InputType::Slider;
            std::function<void(Component *comp, float value)> callback;
            std::pair<std::string, std::string>font;
            void init(std::string id, float value, std::function<void(Component *comp, float value)> callback);
        public:
            static FloatInput *create(std::string id, float value, std::function<void(Component *comp, float value)> callback);
            FloatInput *setValue(float value);
            float getValue();
            FloatInput *setCallback(std::function<void(Component *comp, float value)> callback);
            std::function<void(Component *comp, float value)> getCallback();
            FloatInput *setType(InputType type);
            InputType getType();
            FloatInput *setMin(float min);
            float getMin();
            FloatInput *setMax(float max);
            float getMax();
            FloatInput *setFont(std::pair<std::string, std::string>font);
            std::pair<std::string, std::string>getFont();
            void renderImgui() override;
            CCNode *createCocosNode() override;
    };

    // Dropdown

    class Dropdown : public Component {
        protected:
            std::vector<std::string> options;
            int selected;
            std::function<void(Component *comp, std::string value)> callback;
            std::map<std::string, std::pair<std::string, std::string>> fonts;
            void init(std::string id, std::vector<std::string> options, std::string selected, std::function<void(Component *comp, std::string value)> callback);
        public:
            static Dropdown *create(std::string id, std::vector<std::string> options, std::string selected, std::function<void(Component *comp, std::string value)> callback);
            Dropdown *setOptions(std::vector<std::string> options);
            std::vector<std::string> getOptions();
            Dropdown *setSelected(int selected);
            Dropdown *setSelected(std::string selected);
            std::string getSelected();
            int getSelectedIndex();
            Dropdown *setCallback(std::function<void(Component *comp, std::string value)> callback);
            std::function<void(Component *comp, std::string value)> getCallback();
            Dropdown *setFont(std::string option, std::pair<std::string, std::string>font);
            std::pair<std::string, std::string>getFont(std::string option);
            Dropdown *setFonts(std::map<std::string, std::pair<std::string, std::string>>fonts);
            std::map<std::string, std::pair<std::string, std::string>>getFonts();
            void renderImgui() override;
            CCNode *createCocosNode() override;
    };
}