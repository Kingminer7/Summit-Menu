#pragma once

#include <functional>
#include <map>

namespace summit {
  class LoadManager {
    public:
      enum class LoadType {
        MenuLayer,
        Initial,
      };
    protected:
      static LoadManager *m_instance;
      std::multimap<int, std::pair<std::function<void ()>, LoadType>> m_callbacks = {};
    public:
      static LoadManager *get();
      
      void onLoad(std::function<void ()> function, LoadType loadType = LoadType::MenuLayer, int prio = 0);
      std::multimap<int, std::pair<std::function<void ()>, LoadType>> getCallbacks();
  };
}

// Borrowed and migrated from geode's $on_mod
// clang-format off
#define $onLoad(loadType, prio) \
namespace { \
  struct GEODE_CONCAT(ExecFuncUnique, __LINE__) { \
    GEODE_CONCAT(ExecFuncUnique, __LINE__)() { \
      summit::LoadManager::get()->onLoad([]() { \
        GEODE_CONCAT(ExecFuncUnique, __LINE__)::exec(); \
      }, summit::LoadManager::LoadType::loadType, prio); \
    } \
    static void exec(); \
  }; \
  static GEODE_CONCAT(ExecFuncUnique, __LINE__) GEODE_CONCAT(instance, __LINE__); \
} \
void GEODE_CONCAT(ExecFuncUnique, __LINE__)::exec()
// clang-format on
