#pragma once

namespace summit::hacks {
    class Hack {
        public:
            Hack(){};
            virtual void init() = 0;
            virtual std::string getId() = 0;
            virtual std::string getTab() = 0;
            virtual void update(float) = 0;
    };

    std::map<std::string, Hack*> getHacks();
    std::map<std::string, Hack*> getHacks(std::string tab);
    void registerHack(std::string id, Hack *hack);
    Hack *getHack(std::string id);
    void removeHack(std::string id);
    void init();

    #define RegisterHack(T) $on_mod(Loaded) { auto h = new T; summit::hacks::registerHack(h->getId(), h); }
}