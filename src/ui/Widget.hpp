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
            void setText(std::string text);
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
            void setCallback(std::function<void(Component *comp)> callback);
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
            void setValue(bool value);
            bool getValue();
            void setCallback(std::function<void(Component *comp, bool value)> callback);
            std::function<void(Component *comp, bool value)> getCallback();
            void renderImgui() override;
            CCNode *createCocosNode() override;
    };
}