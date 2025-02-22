#pragma once

#include <map>
#include <string>
#include <utils/LoadManager.hpp>

namespace summit::hacks {
  class Hack {
    public:
      virtual std::string getId() = 0;
      virtual void init() = 0;
      virtual void update(float dt) {};
  };

  class HackManager {
    protected:
      HackManager(){};

      static HackManager *m_instance;
      std::map<std::string, Hack*> m_hacks = {};
    public:
      static HackManager *get();

      void registerHack(Hack *hack);
      Hack *getHack(std::string id);
      std::map<std::string, Hack*> getHacks();
  };

  #define RegisterHack(Hack) $onLoad(Initial, 0) { HackManager::get()->registerHack(new Hack); }
}