#include "Utils.hpp"
#include "hacks/Hack.hpp"

namespace summit {
    UpdateManager *UpdateManager::get() {
        if (!instance) instance = new UpdateManager();
        return instance;
    }

    void UpdateManager::update(float dt)  {
        for (auto& [id, hack] : summit::hacks::getHacks()) {
            hack->update(dt);
        }
        for (auto& [id, callback] : callbacks) {
            callback(dt);
        }
    }

    bool UpdateManager::registerUpdate(std::string id, std::function<void(float)> update) {
        if (callbacks.find(id) != callbacks.end()) return false;
        callbacks[id] = update;
        return true;
    }

    bool UpdateManager::removeUpdate(std::string id) {
        if (callbacks.find(id) == callbacks.end()) return false;
        callbacks.erase(id);
        return true;
    }

    UpdateManager* UpdateManager::instance = nullptr;
}