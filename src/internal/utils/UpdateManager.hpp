#pragma once

#include "Geode/cocos/base_nodes/CCNode.h"
#include <map>
#include <string>

namespace summit {
  class UpdateManager : cocos2d::CCNode {
    protected:
      static UpdateManager *m_instance;
      std::list<std::string> m_disabled = {};
      std::map<std::string, std::function<void (float dt)>> m_callbacks = {};
      bool init() override;

      void update(float dt) override;
    public:
      static UpdateManager *get();

      
      void registerUpdate(std::string id, std::function<void (float dt)> callback, bool enabled = true);
      void removeUpdate(std::string id);
      void enableUpdate(std::string id);
      void disableUpdate(std::string id);
      std::map<std::string, std::function<void (float dt)>> getCallbacks();
  };
}