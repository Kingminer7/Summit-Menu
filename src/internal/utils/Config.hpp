#pragma once

#include <matjson.hpp>

namespace summit {
  class Config {
    protected:
      static matjson::Value temp;
      static matjson::Value saved;
      
      static bool initialized;
    public:
      static void init();
      static void save();

      template<typename T>
      static T get(std::string key, T default_, bool isTemp = false) {
        if (!initialized) return nullptr;
        if (isTemp)
          return temp.get<T>(key) || default_;
        else
          return saved.get<T>(key) || default_;
      }

      template<typename T>
      static T set(std::string key, T value, bool isTemp = false) {
        if (!initialized) return nullptr;
        if (isTemp)
          return temp.set(key, value);
        else
          return saved.set(key, value);
      }
  };
}