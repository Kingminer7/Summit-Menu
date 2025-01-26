#include <Loader.hpp>
#pragma once

namespace summit::hacks {
    class Hack {
        public:
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

    #define RegisterHack(T) $execute { registerHack(new T); }; 
}