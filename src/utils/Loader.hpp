#pragma once

namespace summit {

enum class LoadTime {
  Early,
  MenuLayer,
};
class Loader {
  public:
    static std::multimap<int, std::pair<std::function<void ()>, LoadTime>> callbacks;
    static void onLoad(std::function<void()> func, int prio = 0, LoadTime loadTime = LoadTime::MenuLayer);
    static void onLoad(std::function<void()> func, LoadTime loadTime, int prio = 0);
};
} // namespace summit