#pragma once

namespace summit {
    class Config {
        protected:
            static matjson::Value saved;
            static matjson::Value temp;
            static bool initialized;
        public:
            static void save();
            static void load(bool resetTemp = false);
            static void init();
            static matjson::Value getAllSaved() {
                if (!initialized) init();
                return saved;
            }

            template<typename T>
            static T get(std::string key, T defaultValue, bool isSaved = true) {
                if (!initialized) init();
                if (isSaved) {
                    return saved[key].as<T>().unwrapOr(defaultValue);
                } else {
                    return temp[key].as<T>().unwrapOr(defaultValue);
                }
            }

            template<typename T>
            static void set(std::string key, T value, bool saves = true) {
                if (!initialized) init();
                if (saves) {
                    saved[key] = value;
                    save();
                } else {
                    temp[key] = value;
                }
            }

            template<typename T>
            static void setIfUnset(std::string key, T value, bool saves = true) {
                if (!initialized) init();
                if (saves) {
                    if (!saved.contains(key)) {
                        saved[key] = value;
                        save();
                    }
                } else {
                    if (!temp.contains(key)) {
                        temp[key] = value;
                    }
                }
            }
    };

    class UpdateManager : public cocos2d::CCObject {
        protected:
            UpdateManager() {
                cocos2d::CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(UpdateManager::update), this, 0, false);
            }
            static UpdateManager *instance;
            std::map<std::string, std::function<void(float)>> callbacks;
        public:
            static UpdateManager* get();
            void update(float dt);
            bool registerUpdate(std::string id, std::function<void(float)> func);
            bool removeUpdate(std::string id);
    };
}