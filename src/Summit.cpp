#include "Summit.hpp"
#include "KeyManager.hpp"
#include "hacks/Hack.hpp"

using namespace geode::prelude;

namespace summit {
    bool Config::initialized = false;

    matjson::Value Config::saved = matjson::makeObject({});
    matjson::Value Config::temp = matjson::makeObject({});

    void Config::init() {
        if (initialized) return;
        saved = Mod::get()->getSavedValue<matjson::Value>("config", matjson::makeObject({}));
        temp = matjson::makeObject({});
        initialized = true;
    }

    void Config::save() {
        if (!initialized) init();
        Mod::get()->setSavedValue<matjson::Value>("config", saved);
    }

    void Config::load(bool resetTemp) {
        if (!initialized) init();
        saved = Mod::get()->getSavedValue<matjson::Value>("config", matjson::makeObject({}));
        if (resetTemp) temp = matjson::makeObject({});
    }


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

$on_mod(Loaded) {
    summit::Config::init();
    summit::UpdateManager::get();
    summit::hacks::init();
    summit::utils::KeyManager::loadBinds();
}