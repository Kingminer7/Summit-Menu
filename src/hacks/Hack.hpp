#pragma once

namespace summit::hacks {
    class Hack {
        public:
            Hack(){};
            /**
            @brief Calls when the hack is initialized.
            */
            virtual void init() = 0;

            /**
            @brief Called when Cocos update runs.
            @param dt The time since the last update.
            */
            virtual void update(float dt) {};

            /**
            @brief Gets the ID of the hack.
            @return The ID of the hack.
            */
            virtual std::string getId() = 0;
            
            /**
            @brief Gets the tab of the hack.
            @return The tab of the hack.
            */
            virtual std::string getTab() = 0;
    };

    /**
    @brief Gets all registered hacks.
    @return A map of IDs and hacks.
    */
    std::map<std::string, Hack*> getHacks();
    
    /**
    @brief Gets all registered hacks.
    @param tab The tab to get the hacks from.
    @return A map of IDs and hacks.
    */
    std::map<std::string, Hack*> getHacks(std::string tab);

    /**
    @brief Registers a hack.
    @param hack The hack to register.
    @return Whether it registered successfully.
    */
    bool registerHack(Hack *hack);

    /**
    @brief Gets a hack by ID.
    @param id The id of the hack to get.
    @return The hack with the id, or nullptr if none.
    */
    Hack *getHack(std::string id);

    /**
    @brief Removes a hack by ID.
    @param id The id of the hack to remove.
    @return Whether it removed successfully.
    */
    bool removeHack(std::string id);

    /**
    @brief Initializes the Hack system.
    */
    void init();

    #define RegisterHack(T) $on_mod(Loaded) { summit::hacks::registerHack(new T); }
    #define RegisterTab(tab) $on_mod(Loaded) { summit::hacks::registerTab(tab) }
}