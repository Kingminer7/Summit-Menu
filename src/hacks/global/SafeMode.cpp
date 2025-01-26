#include "../Hack.hpp"
#include <utils/Config.hpp>
#include <ui/Widget.hpp>
#include <utils/HookManager.hpp>
#include <Geode/modify//PlayLayer.hpp>

namespace summit::hacks::global {
  class SafeMode : public Hack {
    public:
      ui::Component *comp;
      void init() {
        comp = ui::ToggleComponent::create("global.safemode", "Safe Mode", Config::get("global.safemode", false), [](bool toggled){});
        ui::Widget::create("global.safemode", comp)->registerWidget("Global");
      }

      std::string getId() {
          return "global.safemode";
      }
      std::string getTab() {
        return "Global";
      }
  };

  class $modify (PlayLayer) {
    void levelComplete() {
        if (summit::Config::get<bool>("global.safemode.enabled", false)) {
            auto orig = m_isTestMode;
            m_isTestMode = true;
            PlayLayer::levelComplete();
            m_isTestMode = orig;
        } else PlayLayer::levelComplete();
    }

    void destroyPlayer(PlayerObject *p, GameObject *g) {
        if (summit::Config::get<bool>("global.safemode.enabled", false)) {
            auto orig = m_isTestMode;
            m_isTestMode = true;
            PlayLayer::destroyPlayer(p,g);
            m_isTestMode = orig;
        } else PlayLayer::destroyPlayer(p,g);
    }

    static void onModify(auto& self) {
      SETUP_HOOK("global.safemode", "PlayLayer::levelComplete", false)
      SETUP_HOOK("global.safemode", "PlayLayer::destroyPlayer", false)
    }
  };

  RegisterHack(SafeMode)
}