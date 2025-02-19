#pragma once

#include "Geode/cocos/base_nodes/CCNode.h"
#include <map>
#include <string>

namespace summit {
  class UpdateManager : cocos2d::CCNode {
    protected:
      static UpdateManager *instance;
      std::list<std::string> disabled = {};
      std::map<std::string, std::function<void (float dt)>> callbacks = {};
      bool init() override;

      void update(float dt) override;
    public:
      static UpdateManager *get();

      
      void registerUpdate(std::string id, std::function<void (float dt)> callback);
      void removeUpdate(std::string id);
      void enableUpdate(std::string id);
      void disableUpdate(std::string id);
      std::map<std::string, std::function<void (float dt)>> getCallbacks();
  };
}