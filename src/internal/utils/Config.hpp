#pragma once

#include <matjson.hpp>

namespace summit {
  class Config {
    protected:
      static matjson::Value m_temp;
      static matjson::Value m_saved;
      
      static bool m_inited;
    public:
      static void init();
      static void save();

      template<typename T>
      static T get(std::string key, T default_, bool isTemp = false) {
        if (!m_inited) return nullptr;
        if (isTemp)
          return m_temp.get<T>(key) || default_;
        else
          return m_saved.get<T>(key) || default_;
      }

      template<typename T>
      static T set(std::string key, T value, bool isTemp = false) {
        if (!m_inited) return nullptr;
        if (isTemp)
          return m_temp.set(key, value);
        else
          return m_saved.set(key, value);
      }
  };
}