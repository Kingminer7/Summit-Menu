#pragma once

#include <map>
#include <functional>

namespace summit {

enum class LoadTime {
  Early,
  MenuLayer,
};
class LoadManager {
  protected:
    static LoadManager *instance;
    LoadManager () {}
    std::multimap<int, std::pair<std::function<void ()>, LoadTime>> callbacks = {};
  public:
    static void onLoad(std::function<void()> func, int prio = 0, LoadTime loadTime = LoadTime::MenuLayer);
    static void onLoad(std::function<void()> func, LoadTime loadTime, int prio = 0);
    static std::multimap<int, std::pair<std::function<void ()>, LoadTime>> *getCallbacks();
};
} // namespace summit