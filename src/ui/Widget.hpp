#pragma once

using namespace geode::prelude;

namespace summit::ui {
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

            Widget() {};

            void init(std::string id);
        public:
            static Widget *create(std::string id);

            std::string getId();
            Component *getComponent(std::string id);
            std::unordered_map<std::string, Component*> getComponents();
            std::vector<std::string> getOrder();
            void addComponent(Component *component);
            void removeComponent(std::string id);

            void renderImgui();
            CCNode *createCocosNode();
    };

    class Label : public Component {
        protected:
            std::string text;
            void init(std::string id, std::string text);
        public:
            static Label *create(std::string id, std::string text);
            Label *setText(std::string text);
            std::string getText();
            void renderImgui() override;
            CCNode *createCocosNode() override;
    };

    class Button : public Component {
        protected:
            std::function<void(Component *comp)> callback;
            void init(std::string id, std::function<void(Component *comp)> callback);
        public:
            static Button *create(std::string id, std::function<void(Component *comp)> callback);
            Button *setCallback(std::function<void(Component *comp)> callback);
            std::function<void(Component *comp)> getCallback();
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
            void renderImgui() override;
            CCNode *createCocosNode() override;
    };
}