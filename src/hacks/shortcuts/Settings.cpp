#include "../Hack.hpp"
#include <utils/Config.hpp>
#include <ui/Widget.hpp>
#include <utils/HookManager.hpp>

namespace summit::hacks::shortcuts {
  class Settings : public Hack {
    public:
      void init() {
        ui::ButtonComponent::create("shortcuts.settings", "Settings", [](){
          OptionsLayer* layer = OptionsLayer::create();
          cocos2d::CCScene* scene = cocos2d::CCDirector::get()->getRunningScene();
          int z = scene->getHighestChildZ();
          if(z == INT_MAX) return;
          layer->setZOrder(z + 1);
          layer->showLayer(false);
          layer->removeFromParentAndCleanup(false);
          scene->addChild(layer);
        })->setTab("Shortcuts")->reg();
        
      }

      std::string getId() {
          return "shortcuts.settings";
      }
      std::string getTab() {
        return "Shortcuts";
      }
  };

  RegisterHack(Settings)
}