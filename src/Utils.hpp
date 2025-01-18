namespace summit {
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