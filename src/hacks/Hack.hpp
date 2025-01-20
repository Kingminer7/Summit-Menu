#pragma once

namespace summit::hacks {
    class Hack {
        public:
            Hack(){};

            virtual void init() = 0;
            virtual void update(float dt) {};

            virtual std::string getId() = 0;
            virtual std::string getTab() = 0;
    };

    void init();

    std::map<std::string, Hack*> getHacks();
    std::map<std::string, Hack*> getHacks(std::string tab);
    Hack *getHack(std::string id);
    bool registerHack(Hack *hack);
    bool removeHack(std::string id);
    
    bool registerTab(std::string tab);
    bool removeTab(std::string tab);
    std::vector<std::string> getTabs();

    #define RegisterHack(T) $on_mod(Loaded) { registerHack(new T); }
    #define RegisterTab(tab) $on_mod(Loaded) { registerTab(tab); }
}