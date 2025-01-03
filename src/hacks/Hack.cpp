#include "Hack.hpp"

namespace summit::hacks {
    std::map <std::string, Hack *> hacks = {};
    
    std::map <std::string, Hack *> getHacks() {
        return hacks;
    }

    std::map <std::string, Hack *> getHacks(std::string tab) {
        std::map <std::string, Hack *> tabHacks = {};
        for (auto hack : hacks) {
            if (hack.second->getTab() == tab) {
                tabHacks[hack.first] = hack.second;
            }
        }
        return tabHacks;
    }

    void registerHack(std::string id, Hack *hack) {
        if (hacks.find(id) != hacks.end()) return;
        hacks[id] = hack;
    }

    Hack *getHack(std::string id) {
        return hacks[id];
    }

    void removeHack(std::string id) {
        hacks.erase(id);
    }

    void init() {
        for (auto& [id, hack] : hacks) {
            hack->init();
        }
    }
}