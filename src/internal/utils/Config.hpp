#pragma once

#include "Geode/loader/Log.hpp"
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
        if (!m_inited) {
          geode::log::error("Unable to get config value {} - not initialized!", key);
          return default_;
        }
        if (isTemp)
          return m_temp[key].as<T>().unwrapOr(default_);
        else
          return m_saved[key].as<T>().unwrapOr(default_);
      }

      template<typename T>
      static void set(std::string key, T value, bool isTemp = false) {
        if (!m_inited) return geode::log::error("Unable to set config value {} - not initialized!", key);
        if (isTemp)
          m_temp.set(key, value);
        else
          m_saved.set(key, value);
      }
  };
}