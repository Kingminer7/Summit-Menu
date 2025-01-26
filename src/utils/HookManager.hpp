#ifdef im_disabling_this_for_now
#include "Geode/loader/Hook.hpp"
namespace summit {
  class HookManager {
    protected:
      static std::map<std::string, std::shared_ptr<geode::Hook>> hooks;
    public: 
      static bool registerHook(std::string id, std::shared_ptr<geode::Hook> hook);
      static bool enableHook(std::string id);
      static bool disableHook(std::string id);
  };

  #define SETUP_HOOK(ns, id, enabled) do { \
    auto hookres = self.getHook(id); \
    if (!hookres) return; \
    auto hook = hookres.unwrap(); \
    hook->setAutoEnable(enabled); \
    HookManager::registerHook(fmt::format("{}/{}", ns, id), hook); \
  } while (0);
}
#endif