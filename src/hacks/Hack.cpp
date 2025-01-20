#include "Hack.hpp"

namespace summit::hacks {
    std::map <std::string, Hack *> hacks = {};
    std::vector<std::string> tabs = {};
    
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

    bool registerHack(Hack *hack) {
        if (!hack) return false;
        if (hacks.find(hack->getId()) != hacks.end()) return false;
        hacks[hack->getId()] = hack;
        return true;
    }

    Hack *getHack(std::string id) {
        return hacks[id];
    }

    bool removeHack(std::string id) {
        if (hacks.find(id) == hacks.end()) return false;
        hacks.erase(id);
        return true;
    }

    bool registerTab(std::string tab) {
        if (std::find(tabs.begin(), tabs.end(), tab) != tabs.end()) return false;
        tabs.push_back(tab);
        return true;
    }

    bool removeTab(std::string tab) {
        auto it = std::find(tabs.begin(), tabs.end(), tab);
        if (it == tabs.end()) return false;
        tabs.erase(it);
        return true;
    }

    std::vector<std::string> getTabs() {
        return tabs;
    }

    void init() {
        for (auto& [id, hack] : hacks) {
            hack->init();
        }
    }

    RegisterTab("test")
}